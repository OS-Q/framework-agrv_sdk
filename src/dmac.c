#include "dmac.h"

void DMAC_Init(void)
{
  DMAC->Configuration = 0;
  for (int i = 0; i < DMAC_CHANNELS; i++) {
    DMAC->Channels[i].Configuration = 0;
  }
  DMAC->IntErrorClear = 0xFFFFFFFF;
  DMAC->IntTCClear    = 0xFFFFFFFF;
  DMAC->Configuration = DMAC_M1_LITTLE_ENDIAN | DMAC_M2_LITTLE_ENDIAN | ENABLE;
}

void DMAC_HaltChannel(DMAC_ChannelNumTypeDef channel)
{
  // To avoid losing data in FIFO, set the halt bit so that any subsequent DMA request is ignored. Then disable the
  // channel after it is no longer active
  DMAC->Channels[channel].Configuration |= (1 << DMAC_CHANNEL_HALT_OFFSET);
  while (DMAC->Channels[channel].Configuration & (1 << DMAC_CHANNEL_ACTIVE_OFFSET));
  DMAC_DisableChannel(channel);
}

// Config function to initiate 1 DMA transfer. Transfer size cannot exceed DMAC_MAX_TRANSFER_SIZE
void DMAC_Config(DMAC_ChannelNumTypeDef channel, uint32_t srcAddr, uint32_t dstAddr,
                 DMAC_AddrIncTypeDef srcIncr, DMAC_AddrIncTypeDef dstIncr,
                 DMAC_WidthTypeDef srcWidth, DMAC_WidthTypeDef dstWidth,
                 DMAC_BurstTypeDef srcBurst, DMAC_BurstTypeDef dstBurst,
                 uint32_t transferSize, DMAC_FlowControlTypeDef transferType,
                 uint32_t srcPeripheral, uint32_t dstPeripheral)
{
  DMAC_ClearChannelIntError(channel);
  DMAC_ClearChannelIntTC(channel);

  DMAC_SetSrcAddress   (channel, srcAddr);
  DMAC_SetDstAddress   (channel, dstAddr);
  DMAC_SetLLI          (channel, 0);
  DMAC_SetControl      (channel, DMAC_MakeControl(srcIncr, dstIncr, srcWidth, dstWidth,
                                                  srcBurst, dstBurst, transferSize, ENABLE));
  DMAC_SetConfiguration(channel, DMAC_MakeConfiguration(transferType, srcPeripheral, dstPeripheral));
}

// Config function to initiate DMA from the first link list item
void DMAC_ConfigLLI(DMAC_ChannelNumTypeDef channel, DMAC_FlowControlTypeDef transferType,
                    uint32_t srcPeripheral, uint32_t dstPeripheral, uint32_t lli)
{
  DMAC_ClearChannelIntError(channel);
  DMAC_ClearChannelIntTC(channel);

  DMAC_LLI_TypeDef *ptr = (DMAC_LLI_TypeDef *)lli;

  DMAC_SetSrcAddress   (channel, ptr->SrcAddr);
  DMAC_SetDstAddress   (channel, ptr->DstAddr);
  DMAC_SetLLI          (channel, ptr->LLI);
  DMAC_SetControl      (channel, ptr->Control);
  DMAC_SetConfiguration(channel, DMAC_MakeConfiguration(transferType, srcPeripheral, dstPeripheral));
}

// The lli must be valid in memory throughout the transfer
void DMAC_ConfigCircular(DMAC_ChannelNumTypeDef channel, uint32_t srcAddr, uint32_t dstAddr,
                         DMAC_AddrIncTypeDef srcIncr, DMAC_AddrIncTypeDef dstIncr,
                         DMAC_WidthTypeDef srcWidth, DMAC_WidthTypeDef dstWidth,
                         DMAC_BurstTypeDef srcBurst, DMAC_BurstTypeDef dstBurst,
                         uint32_t transferSize, DMAC_FlowControlTypeDef transferType,
                         uint32_t srcPeripheral, uint32_t dstPeripheral, DMAC_LLI_TypeDef *lli)
{
  lli->SrcAddr = srcAddr;
  lli->DstAddr = dstAddr;
  lli->Control = DMAC_MakeControl(srcIncr, dstIncr, srcWidth, dstWidth, srcBurst, dstBurst, transferSize, ENABLE);
  lli->LLI     = (uint32_t)lli; // Points to itself for circular transfer
  DMAC_ConfigLLI(channel, transferType, srcPeripheral, dstPeripheral, (uint32_t)lli);
}


// This function can handle any transfer size. If the size is greater than DMAC_MAX_TRANSFER_SIZE, link list items will 
// be automatically allocated and returned. The caller should deallocate the memory after all items are finished. 
// Alternatively, an LLI array can be given such that no memory allocation is necessary. In this case the caller must 
// make sure that the LLI array is valid in memory throughout the transfer.
DMAC_LLI_TypeDef *DMAC_AutoTransfer(DMAC_ChannelNumTypeDef channel, uint32_t srcAddr, uint32_t dstAddr,
                                    DMAC_AddrIncTypeDef srcIncr, DMAC_AddrIncTypeDef dstIncr,
                                    DMAC_WidthTypeDef srcWidth, DMAC_WidthTypeDef dstWidth,
                                    DMAC_BurstTypeDef srcBurst, DMAC_BurstTypeDef dstBurst,
                                    uint32_t transferSize, DMAC_FlowControlTypeDef transferType,
                                    uint32_t srcPeripheral, uint32_t dstPeripheral,
                                    EnableTypeDef enableIntTC, DMAC_LLI_TypeDef *lli_arr)
{
  DMAC_LLI_TypeDef  lli_val; // The first lli
  DMAC_LLI_TypeDef *lli_ptr = lli_arr;

  const int LLI_COUNT = (transferSize + DMAC_MAX_TRANSFER_SIZE - 1) / DMAC_MAX_TRANSFER_SIZE;
  if (LLI_COUNT > 1 && !lli_ptr) {
    lli_ptr = AlignedMalloc(4, (LLI_COUNT - 1) * sizeof(DMAC_LLI_TypeDef));
  }
  
  for (int i = 0; i < LLI_COUNT; ++i) {
    DMAC_LLI_TypeDef *lli = (i == 0) ? &lli_val : lli_ptr + (i - 1);
    lli->SrcAddr = srcAddr + (srcIncr == DMAC_ADDR_INCR_ON ? i * DMAC_MAX_TRANSFER_SIZE * (1 << srcWidth) : 0);
    lli->DstAddr = dstAddr + (dstIncr == DMAC_ADDR_INCR_ON ? i * DMAC_MAX_TRANSFER_SIZE * (1 << srcWidth) : 0);
    lli->LLI     = (i < LLI_COUNT - 1) ? (uint32_t)(lli_ptr + i) : 0;
    lli->Control = DMAC_MakeControl(srcIncr, dstIncr, srcWidth, dstWidth, srcBurst, dstBurst,
                                      (i < LLI_COUNT - 1) ? DMAC_MAX_TRANSFER_SIZE : transferSize - (LLI_COUNT - 1) * DMAC_MAX_TRANSFER_SIZE,
                                      (i < LLI_COUNT - 1) ?  DISABLE : enableIntTC); // Interrupt only for the last lli
  }
  DMAC_ConfigLLI(channel, transferType, srcPeripheral, dstPeripheral, (uint32_t)(&lli_val));
  return lli_ptr;
}

void DMAC_WaitedTransfer(DMAC_ChannelNumTypeDef channel, uint32_t srcAddr, uint32_t dstAddr,
                         DMAC_AddrIncTypeDef srcIncr, DMAC_AddrIncTypeDef dstIncr,
                         DMAC_WidthTypeDef srcWidth, DMAC_WidthTypeDef dstWidth,
                         DMAC_BurstTypeDef srcBurst, DMAC_BurstTypeDef dstBurst,
                         uint32_t transferSize, DMAC_FlowControlTypeDef transferType,
                         uint32_t srcPeripheral, uint32_t dstPeripheral)
{
  while (transferSize > 0) {
    uint32_t size = transferSize > DMAC_MAX_TRANSFER_SIZE ? DMAC_MAX_TRANSFER_SIZE : transferSize;
    DMAC_Config(channel, srcAddr, dstAddr, srcIncr, dstIncr, srcWidth, dstWidth, srcBurst, dstBurst,
                size, transferType, srcPeripheral, dstPeripheral);
    transferSize -= size;
    srcAddr += (srcIncr == DMAC_ADDR_INCR_ON ? (size * (1 << srcWidth)) : 0);
    dstAddr += (dstIncr == DMAC_ADDR_INCR_ON ? (size * (1 << srcWidth)) : 0);
    DMAC_WaitChannel(channel);
    DMAC_ClearChannelIntTC(channel);
  }
}
