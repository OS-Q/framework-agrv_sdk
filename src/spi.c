#include "spi.h"

void SPI_Init(SPI_TypeDef *spi, SPI_SclkDivTypeDef div)
{
  SPI_Reset(spi);
  spi->CTRL = div | SPI_CTRL_LITTLE_ENDIAN;
}

void SPI_Send(SPI_TypeDef *spi, int tx_bytes, const uint32_t tx_data)
{
  // When sending more than 4 bytes, the first 4 bytes are from tx_data and the rest are dummy.
  ASSERT(tx_bytes <= SPI_PHASE_BYTE_CNT_MAX);
  SPI_SetPhaseCtrl(spi, SPI_PHASE_0, SPI_PHASE_ACTION_TX, SPI_PHASE_MODE_SINGLE, tx_bytes);
  SPI_SetPhaseData(spi, SPI_PHASE_0, tx_data);
  SPI_Start(spi, SPI_CTRL_PHASE_CNT1, SPI_CTRL_DMA_OFF, SPI_INTERRUPT_OFF);
  SPI_WaitForDone(spi);
}

void SPI_SendDMA(SPI_TypeDef *spi, int tx_bytes, const uint32_t *tx_data, DMAC_ChannelNumTypeDef channel)
{
  ASSERT(tx_bytes <= SPI_PHASE_BYTE_CNT_MAX);
  SPI_SetPhaseCtrl(spi, SPI_PHASE_0, SPI_PHASE_ACTION_TX, SPI_PHASE_MODE_SINGLE, tx_bytes);
  DMAC_Config(channel, (uint32_t)tx_data, (uint32_t)&spi->PHASE_DATA[SPI_PHASE_0],
              DMAC_ADDR_INCR_ON, DMAC_ADDR_INCR_OFF, DMAC_WIDTH_32_BIT, DMAC_WIDTH_32_BIT,
              DMAC_BURST_1, DMAC_BURST_1, 0, DMAC_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL,
              0, SPI_TX_DMA_REQ(spi));
  SPI_Start(spi, SPI_CTRL_PHASE_CNT1, SPI_CTRL_DMA_ON, SPI_INTERRUPT_OFF);
  SPI_WaitForDone(spi);
  DMAC_HaltChannel(channel);
}

uint32_t SPI_SendAndReceive(SPI_TypeDef *spi, int tx_bytes, const uint32_t tx_data, int rx_bytes)
{
  // When sending more than 4 bytes, the first 4 bytes are from tx_data and the rest are dummy.
  ASSERT(tx_bytes <= SPI_PHASE_BYTE_CNT_MAX && rx_bytes <= 4); // Can receive up to 4 bytes.
  SPI_SetPhaseCtrl(spi, SPI_PHASE_0, SPI_PHASE_ACTION_TX, SPI_PHASE_MODE_SINGLE, tx_bytes);
  SPI_SetPhaseData(spi, SPI_PHASE_0, tx_data);
  if (SPI_RX_PIPELINE) {
    SPI_SetPhaseCtrl(spi, SPI_PHASE_1, SPI_PHASE_ACTION_DUMMY_TX, SPI_PHASE_MODE_QUAD, 1);
  }
  SPI_SetPhaseCtrl(spi, SPI_RX_PIPELINE ? SPI_PHASE_2 : SPI_PHASE_1, SPI_PHASE_ACTION_RX, SPI_PHASE_MODE_SINGLE, rx_bytes);
  SPI_Start(spi, SPI_RX_PIPELINE ? SPI_CTRL_PHASE_CNT3 : SPI_CTRL_PHASE_CNT2, SPI_CTRL_DMA_OFF, SPI_INTERRUPT_OFF);
  SPI_WaitForDone(spi);
  return SPI_GetPhaseData(spi, SPI_RX_PIPELINE ? SPI_PHASE_2 : SPI_PHASE_1);
}

void SPI_SendAndReceiveDMA(SPI_TypeDef *spi, int tx_bytes, const uint32_t *tx_data,
                           int rx_bytes, uint32_t *rx_data, DMAC_ChannelNumTypeDef channel)
{
  ASSERT(tx_bytes <= (SPI_RX_PIPELINE ? 24 : 28) && rx_bytes <= SPI_PHASE_BYTE_CNT_MAX);
  SPI_PhaseNumberTypeDef phase = SPI_PHASE_0;
  while (tx_bytes > 0) {
    int bytes = tx_bytes > 4 ? 4 : tx_bytes;
    SPI_SetPhaseCtrl(spi, phase, SPI_PHASE_ACTION_TX, SPI_PHASE_MODE_SINGLE, bytes);
    SPI_SetPhaseData(spi, phase++, *tx_data++);
    tx_bytes -= bytes;
  }
  if (SPI_RX_PIPELINE) {
    SPI_SetPhaseCtrl(spi, phase++, SPI_PHASE_ACTION_DUMMY_TX, SPI_PHASE_MODE_QUAD, 1);
  }
  SPI_SetPhaseCtrl(spi, phase, SPI_PHASE_ACTION_RX, SPI_PHASE_MODE_SINGLE, rx_bytes);
  DMAC_Config(channel, (uint32_t)&spi->PHASE_DATA[phase], (uint32_t)rx_data,
              DMAC_ADDR_INCR_OFF, DMAC_ADDR_INCR_ON, DMAC_WIDTH_32_BIT, DMAC_WIDTH_32_BIT,
              DMAC_BURST_1, DMAC_BURST_1, 0, DMAC_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL,
              SPI_RX_DMA_REQ(spi), 0);
  SPI_Start(spi, phase << SPI_CTRL_PHASE_CNT_OFFSET, SPI_CTRL_DMA_ON, SPI_INTERRUPT_OFF);
  SPI_WaitForDone(spi);
  DMAC_HaltChannel(channel);
}

void SPI_FLASH_SetCmdPhase(SPI_TypeDef *spi, uint32_t cmd)
{
  // Command phase is always the first phase and tx 1 byte in single mode
  SPI_SetPhaseCtrl(spi, SPI_PHASE_0, SPI_PHASE_ACTION_TX, SPI_PHASE_MODE_SINGLE, 1);
  SPI_SetPhaseData(spi, SPI_PHASE_0, cmd);
}

void SPI_FLASH_SetCmdAddrPhase(SPI_TypeDef *spi, uint32_t cmd, uint32_t addr)
{
  // Command + address make the first phase and tx 4 bytes in single mode
  SPI_SetPhaseCtrl(spi, SPI_PHASE_0, SPI_PHASE_ACTION_TX, SPI_PHASE_MODE_SINGLE, 4);
  addr = SPI_FLASH_ADDR(addr);
  SPI_SetPhaseData(spi, SPI_PHASE_0, cmd | (addr << SPI_PHASE_BYTE_CNT_OFFSET));
}

// 1 byte of command without any extra address or data
void SPI_FLASH_SingleCmd(SPI_TypeDef *spi, uint32_t cmd)
{
  SPI_Send(spi, 1, cmd);
}

// 1 byte of command with 3 bytes of address and no data
void SPI_FLASH_SingleCmdAddr(SPI_TypeDef *spi, uint32_t cmd, uint32_t addr)
{
  SPI_Send(spi, 4, SPI_FLASH_CMD_ADDR(cmd, addr));
}

void SPI_FLASH_WaitForWrite(SPI_TypeDef *spi, SPI_InterruptTypeDef interrupt)
{
  SPI_FLASH_SetCmdPhase(spi, SPI_FLASH_CMD_RDSR);
  if (SPI_RX_PIPELINE) {
    SPI_SetPhaseCtrl(spi, SPI_PHASE_1, SPI_PHASE_ACTION_DUMMY_TX, SPI_PHASE_MODE_QUAD, 1);
  }
  const int rx_phase = SPI_RX_PIPELINE ? SPI_PHASE_2 : SPI_PHASE_1;
  const int phase_cnt = SPI_RX_PIPELINE ? SPI_CTRL_PHASE_CNT3 : SPI_CTRL_PHASE_CNT2;
  SPI_SetPhaseCtrl(spi, rx_phase, SPI_PHASE_ACTION_POLL, SPI_PHASE_MODE_SINGLE, 0);
  SPI_SetPhaseData(spi, rx_phase, SPI_FLASH_WIP_FLAG << 16);
  SPI_Start(spi, phase_cnt, SPI_CTRL_DMA_OFF, interrupt);
  if (interrupt == SPI_INTERRUPT_OFF) {
    SPI_WaitForDone(spi);
  }
}

uint32_t SPI_FLASH_ReadID(SPI_TypeDef *spi)
{
  return SPI_SendAndReceive(spi, 1, SPI_FLASH_CMD_RDID, 3);
}

uint32_t SPI_FLASH_ReadManufacturerID(SPI_TypeDef *spi)
{
  return SPI_SendAndReceive(spi, 4, SPI_FLASH_CMD_ADDR(SPI_FLASH_CMD_REMS, 0), 2);
}

uint32_t SPI_FLASH_GetCapacity(SPI_TypeDef *spi)
{
  return SPI_SendAndReceive(spi, 5, SPI_FLASH_CMD_ADDR(SPI_FLASH_CMD_SFDP, 0x34), 4);
}

void SPI_FLASH_ReadUniqueID(SPI_TypeDef *spi, uint32_t *uid, DMAC_ChannelNumTypeDef channel)
{
  uint32_t data[2] = {SPI_FLASH_CMD_RDUID, 0};
  SPI_SendAndReceiveDMA(spi, 5, data, 16, uid, channel);
}

uint32_t SPI_FLASH_ReleaseDP(SPI_TypeDef *spi)
{
  return SPI_SendAndReceive(spi, 4, SPI_FLASH_CMD_RDP, 1);
}

uint16_t SPI_FLASH_ReadStatus(SPI_TypeDef *spi)
{
  return SPI_SendAndReceive(spi, 1, SPI_FLASH_CMD_RDSR, 1) | SPI_SendAndReceive(spi, 1, SPI_FLASH_CMD_RDSR2, 1) << 8;
}

void SPI_FLASH_WriteStatus(SPI_TypeDef *spi, uint16_t status)
{
  SPI_FLASH_WriteEnable(spi);
  SPI_Send(spi, 3, SPI_FLASH_CMD_WRSR | status << 8);
  SPI_FLASH_WaitForWrite(spi, SPI_INTERRUPT_OFF);
}

void SPI_FLASH_QuadEnable(SPI_TypeDef *spi)
{
  uint16_t status = SPI_FLASH_ReadStatus(spi);
  if (!(status & SPI_FLASH_QE_FLAG)) {
    SPI_FLASH_WriteStatus(spi, status | SPI_FLASH_QE_FLAG);
  } 
}

void SPI_FLASH_QuadDisable(SPI_TypeDef *spi)
{
  uint16_t status = SPI_FLASH_ReadStatus(spi);
  if (status & SPI_FLASH_QE_FLAG) {
    SPI_FLASH_WriteStatus(spi, status & ~SPI_FLASH_QE_FLAG);
  } 
}

void SPI_FLASH_EraseSector(SPI_TypeDef *spi, uint32_t addr, SPI_InterruptTypeDef interrupt)
{
  SPI_FLASH_WriteEnable(spi);
  SPI_FLASH_SingleCmdAddr(spi, SPI_FLASH_CMD_SE, addr);
  SPI_FLASH_WaitForWrite(spi, interrupt);
}

void SPI_FLASH_EraseBlock(SPI_TypeDef *spi, uint32_t addr, SPI_InterruptTypeDef interrupt)
{
  SPI_FLASH_WriteEnable(spi);
  SPI_FLASH_SingleCmdAddr(spi, SPI_FLASH_CMD_BE, addr);
  SPI_FLASH_WaitForWrite(spi, interrupt);
}

void SPI_FLASH_EraseChip(SPI_TypeDef *spi, SPI_InterruptTypeDef interrupt)
{
  SPI_FLASH_WriteEnable(spi);
  SPI_FLASH_SingleCmd(spi, SPI_FLASH_CMD_CE);
  SPI_FLASH_WaitForWrite(spi, interrupt);
}

// Program a flash page, length must be <=256 and the range [addr, addr + length) cannot go across page boundary.
void SPI_FLASH_WritePage(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, uint32_t length, SPI_PhaseModeTypeDef mode,
                         DMAC_ChannelNumTypeDef channel, SPI_InterruptTypeDef interrupt)
{
  uint32_t cmd = mode == SPI_PHASE_MODE_SINGLE ? SPI_FLASH_CMD_PP : mode == SPI_PHASE_MODE_DUAL ? SPI_FLASH_CMD_DPP : SPI_FLASH_CMD_QPP;
  SPI_FLASH_WriteEnable(spi);
  SPI_FLASH_SetCmdAddrPhase(spi, cmd, addr);
  SPI_SetPhaseCtrl(spi, SPI_PHASE_1, SPI_PHASE_ACTION_TX, mode, length);
  DMAC_Config(channel, (uint32_t)buf, (uint32_t)&spi->PHASE_DATA[SPI_PHASE_1],
              DMAC_ADDR_INCR_ON, DMAC_ADDR_INCR_OFF, DMAC_WIDTH_32_BIT, DMAC_WIDTH_32_BIT,
              DMAC_BURST_1, DMAC_BURST_1, 0, DMAC_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL,
              0, SPI_TX_DMA_REQ(spi));
  SPI_Start(spi, SPI_CTRL_PHASE_CNT2, SPI_CTRL_DMA_ON, SPI_INTERRUPT_OFF);
  SPI_WaitForDone(spi);
  DMAC_HaltChannel(channel);
  SPI_FLASH_WaitForWrite(spi, interrupt);
}

void SPI_FLASH_ReadSector(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, uint32_t length, SPI_PhaseModeTypeDef mode,
                          DMAC_ChannelNumTypeDef channel, SPI_InterruptTypeDef interrupt)
{
  length = (length <= SPI_PHASE_BYTE_CNT_MAX ? length : SPI_PHASE_BYTE_CNT_MAX);
  uint32_t cmd = mode == SPI_PHASE_MODE_SINGLE ? SPI_FLASH_CMD_FREAD : mode == SPI_PHASE_MODE_DUAL ? SPI_FLASH_CMD_2READ : SPI_FLASH_CMD_4READ;
  int dummy_bytes = mode == SPI_PHASE_MODE_QUAD ? 3 : 1;
  SPI_FLASH_SetCmdPhase(spi, cmd);
  SPI_SetPhaseCtrl(spi, SPI_PHASE_1, SPI_PHASE_ACTION_TX, mode, 3 + dummy_bytes); // 3 bytes address + dummy
  SPI_SetPhaseData(spi, SPI_PHASE_1, SPI_FLASH_ADDR(addr));
  if (SPI_RX_PIPELINE) {
    SPI_SetPhaseCtrl(spi, SPI_PHASE_2, SPI_PHASE_ACTION_DUMMY_TX, SPI_PHASE_MODE_QUAD, 1);
  }
  int rx_phase = SPI_RX_PIPELINE ? SPI_PHASE_3 : SPI_PHASE_2;
  int phase_cnt = SPI_RX_PIPELINE ? SPI_CTRL_PHASE_CNT4 : SPI_CTRL_PHASE_CNT3;
  SPI_SetPhaseCtrl(spi, rx_phase, SPI_PHASE_ACTION_RX, mode, length);
  DMAC_Config(channel, (uint32_t)&spi->PHASE_DATA[rx_phase], (uint32_t)buf,
              DMAC_ADDR_INCR_OFF, DMAC_ADDR_INCR_ON, DMAC_WIDTH_32_BIT, DMAC_WIDTH_32_BIT,
              DMAC_BURST_1, DMAC_BURST_1, 0, DMAC_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL,
              SPI_RX_DMA_REQ(spi), 0);
  SPI_Start(spi, phase_cnt, SPI_CTRL_DMA_ON, interrupt);
  if (interrupt == SPI_INTERRUPT_OFF) {
    SPI_WaitForDone(spi);
    DMAC_HaltChannel(channel);
  }
}

void SPI_FLASH_Erase(SPI_TypeDef *spi, uint32_t addr, int total)
{
  while (total > 0) {
    uint32_t block_start  = addr & SPI_FLASH_BLOCK_MASK;
    uint32_t sector_start = addr & SPI_FLASH_SECTOR_MASK;
    uint32_t erase_size;
    bool use_block_erase = (addr - block_start + total > SPI_FLASH_BLOCK_SIZE - SPI_FLASH_SECTOR_SIZE);
    if (block_start == sector_start && use_block_erase) {
      erase_size = (block_start + SPI_FLASH_BLOCK_SIZE - addr);
      SPI_FLASH_EraseBlock(spi, addr, SPI_INTERRUPT_OFF);
    } else {
      erase_size = (sector_start + SPI_FLASH_SECTOR_SIZE - addr);
      SPI_FLASH_EraseSector(spi, addr, SPI_INTERRUPT_OFF);
    }
    addr += erase_size;
    total -= erase_size;
  }
}

void SPI_FLASH_Read(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, int total, SPI_PhaseModeTypeDef mode, DMAC_ChannelNumTypeDef channel)
{
  while (total > 0) {
    uint32_t length = total > SPI_PHASE_BYTE_CNT_MAX ? SPI_PHASE_BYTE_CNT_MAX : total;
    SPI_FLASH_ReadSector(spi, buf, addr, length, mode, channel, SPI_INTERRUPT_OFF);
    addr += length ;
    total -= length;
    buf += length / 4;
  }
}

void SPI_FLASH_Write(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, int total, SPI_PhaseModeTypeDef mode, DMAC_ChannelNumTypeDef channel)
{
  while (total > 0) {
    uint32_t length = ((addr + SPI_FLASH_PAGE_SIZE) & SPI_FLASH_PAGE_MASK) - addr;
    if ((int)length > total) {
      length = total;
    }
    SPI_FLASH_WritePage(spi, buf, addr, length, mode, channel, SPI_INTERRUPT_OFF);
    addr += length;
    total -= length;
    buf += length / 4;
  }
}

// SPI PSRAM functions

void SPI_PRAM_EnableQPI(SPI_TypeDef *spi)
{
  SPI_FLASH_SingleCmd(spi, SPI_PSRAM_CMD_QPI_EN);
}

void SPI_PRAM_DisableQPI(SPI_TypeDef *spi)
{
  SPI_SetPhaseCtrl(spi, SPI_PHASE_0, SPI_PHASE_ACTION_TX, SPI_PHASE_MODE_QUAD, 1);
  SPI_SetPhaseData(spi, SPI_PHASE_0, SPI_PSRAM_CMD_QPI_DIS);
  SPI_Start(spi, SPI_CTRL_PHASE_CNT1, SPI_CTRL_DMA_OFF, SPI_INTERRUPT_OFF);
  SPI_WaitForDone(spi);
}

void SPI_PSRAM_WritePage(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, uint32_t length, SPI_PhaseModeTypeDef mode,
                         DMAC_ChannelNumTypeDef channel, SPI_InterruptTypeDef interrupt, bool qpi_mode)
{
  uint32_t cmd = mode == SPI_PHASE_MODE_SINGLE ? SPI_PSRAM_CMD_WRITE : SPI_PSRAM_CMD_QWRITE;
  SPI_SetPhaseCtrl(spi, SPI_PHASE_0, SPI_PHASE_ACTION_TX, qpi_mode ? mode : SPI_PHASE_MODE_SINGLE, 1);
  SPI_SetPhaseData(spi, SPI_PHASE_0, cmd);
  SPI_SetPhaseCtrl(spi, SPI_PHASE_1, SPI_PHASE_ACTION_TX, mode, 3);
  SPI_SetPhaseData(spi, SPI_PHASE_1, SPI_FLASH_ADDR(addr));
  SPI_SetPhaseCtrl(spi, SPI_PHASE_2, SPI_PHASE_ACTION_TX, mode, length);
  DMAC_Config(channel, (uint32_t)buf, (uint32_t)&spi->PHASE_DATA[SPI_PHASE_2],
              DMAC_ADDR_INCR_ON, DMAC_ADDR_INCR_OFF, DMAC_WIDTH_32_BIT, DMAC_WIDTH_32_BIT,
              DMAC_BURST_1, DMAC_BURST_1, 0, DMAC_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL,
              0, SPI_TX_DMA_REQ(spi));
  SPI_Start(spi, SPI_CTRL_PHASE_CNT3, SPI_CTRL_DMA_ON, SPI_INTERRUPT_OFF);
  SPI_WaitForDone(spi);
  DMAC_HaltChannel(channel);
}

void SPI_PSRAM_ReadPage(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, uint32_t length, SPI_PhaseModeTypeDef mode,
                        DMAC_ChannelNumTypeDef channel, SPI_InterruptTypeDef interrupt, bool qpi_mode)
{
  length = (length <= SPI_PHASE_BYTE_CNT_MAX ? length : SPI_PHASE_BYTE_CNT_MAX);
  uint32_t cmd = mode == SPI_PHASE_MODE_SINGLE ? SPI_PSRAM_CMD_READ : SPI_PSRAM_CMD_QREAD;
  int dummy_bytes = mode == SPI_PHASE_MODE_QUAD ? 3 : 1;
  SPI_SetPhaseCtrl(spi, SPI_PHASE_0, SPI_PHASE_ACTION_TX, qpi_mode ? mode : SPI_PHASE_MODE_SINGLE, 1);
  SPI_SetPhaseData(spi, SPI_PHASE_0, cmd);
  SPI_SetPhaseCtrl(spi, SPI_PHASE_1, SPI_PHASE_ACTION_TX, mode, 3 + dummy_bytes); // 3 bytes address + dummy
  SPI_SetPhaseData(spi, SPI_PHASE_1, SPI_FLASH_ADDR(addr));
  if (SPI_RX_PIPELINE) {
    SPI_SetPhaseCtrl(spi, SPI_PHASE_2, SPI_PHASE_ACTION_DUMMY_TX, SPI_PHASE_MODE_QUAD, 1);
  }
  int rx_phase = SPI_RX_PIPELINE ? SPI_PHASE_3 : SPI_PHASE_2;
  int phase_cnt = SPI_RX_PIPELINE ? SPI_CTRL_PHASE_CNT4 : SPI_CTRL_PHASE_CNT3;
  SPI_SetPhaseCtrl(spi, rx_phase, SPI_PHASE_ACTION_RX, mode, length);
  DMAC_Config(channel, (uint32_t)&spi->PHASE_DATA[rx_phase], (uint32_t)buf,
              DMAC_ADDR_INCR_OFF, DMAC_ADDR_INCR_ON, DMAC_WIDTH_32_BIT, DMAC_WIDTH_32_BIT,
              DMAC_BURST_1, DMAC_BURST_1, 0, DMAC_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL,
              SPI_RX_DMA_REQ(spi), 0);
  SPI_Start(spi, phase_cnt, SPI_CTRL_DMA_ON, interrupt);
  if (interrupt == SPI_INTERRUPT_OFF) {
    SPI_WaitForDone(spi);
    DMAC_HaltChannel(channel);
  }
}

void SPI_PSRAM_Write(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, int total, SPI_PhaseModeTypeDef mode,
                     DMAC_ChannelNumTypeDef channel, bool qpi_mode)
{
  while (total > 0) {
    uint32_t length = ((addr + SPI_PSRAM_PAGE_SIZE) & SPI_PSRAM_PAGE_MASK) - addr;
    if ((int)length > total) {
      length = total;
    }
    SPI_PSRAM_WritePage(spi, buf, addr, length, mode, channel, SPI_INTERRUPT_OFF, qpi_mode);
    addr += length;
    total -= length;
    buf += length / 4;
  }
}

void SPI_PSRAM_Read(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, int total, SPI_PhaseModeTypeDef mode,
                    DMAC_ChannelNumTypeDef channel, bool qpi_mode)
{
  while (total > 0) {
    // Don't cross page boundary to achieve higher frequency
    uint32_t length = ((addr + SPI_PSRAM_PAGE_SIZE) & SPI_PSRAM_PAGE_MASK) - addr;
    if ((int)length > total) {
      length = total;
    }
    SPI_PSRAM_ReadPage(spi, buf, addr, length, mode, channel, SPI_INTERRUPT_OFF, qpi_mode);
    addr += length ;
    total -= length;
    buf += length / 4;
  }
}
