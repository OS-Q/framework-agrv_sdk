#include "system.h"
#include "flash.h"
#include "util.h"

void FLASH_Unlock(void)
{
  if (FLASH_IsLocked()) {
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
  }
}

void FLASH_Lock(void)
{
  FLASH->CR |= FLASH_CR_LOCK;
}

void FLASH_OptionByteUnlock(void)
{
  FLASH_Unlock();
  if (FLASH_IsOptionByteLocked()) {
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
  }
}

void FLASH_OptionByteLock(void)
{
  FLASH->CR &= ~FLASH_CR_OPTWRE;
}

uint32_t FLASH_GetFPGAConfigAddress(void)
{
  if (FLASH_OB->FPGA_CONFIG == ~FLASH_OB->FPGA_CONFIGn) {
    return FLASH_OB->FPGA_CONFIG;
  } else {
    return 0;
  }
}

uint32_t FLASH_GetFPGACompressedConfigAddress(void)
{
  if (FLASH_OB->FPGA_COMPRESSED_CONFIG == ~FLASH_OB->FPGA_COMPRESSED_CONFIGn) {
    return FLASH_OB->FPGA_COMPRESSED_CONFIG;
  } else {
    return 0;
  }
}

__attribute__((aligned(64))) // Make sure FLASH_CR_STRT is set when flash is not active
void FLASH_Start(void)
{                   
  UTIL_IdleCycle(SYS_GetSclkDividerHigh() * 256);
  FLASH->CR |= FLASH_CR_STRT;
}
  
void FLASH_EraseOptionByte(void)
{
  FLASH_SetEraseMode(FLASH_EraseTypeOpt);
  FLASH_Start();
  FLASH_WaitForBusy();
  FLASH_SetEraseMode(FLASH_EraseTypeNone);
}

void FLASH_EraseSector(uint32_t addr)
{
  // Sectors are 4KB sized and aligned. Any address in the sector is valid.
  FLASH_SetAddress(addr);
  FLASH_SetEraseMode(FLASH_EraseTypeSector);
  FLASH_Start();
  FLASH_WaitForBusy();
  FLASH_SetEraseMode(FLASH_EraseTypeNone);
}

void FLASH_EraseBlock(uint32_t addr)
{
  // Blocks are 64KB sized and aligned. Any address in the block is valid.
  FLASH_SetAddress(addr);
  FLASH_SetEraseMode(FLASH_EraseTypeBlock);
  FLASH_Start();
  FLASH_WaitForBusy();
  FLASH_SetEraseMode(FLASH_EraseTypeNone);
}

void FLASH_EraseChip(void)
{
  FLASH_SetEraseMode(FLASH_EraseTypeChip);
  FLASH_Start();
  FLASH_WaitForBusy();
  FLASH_SetEraseMode(FLASH_EraseTypeNone);
}

void FLASH_Erase(uint32_t addr, int byte_count)
{
  // Automatically use the fastest way to erase the given address range. The minimum erasable unit is a 4K sector.
  uint32_t addr_begin = addr & ~0xfff;
  uint32_t addr_end   = (addr + byte_count - 1 + FLASH_SECTOR_SIZE) & ~0xfff; // Till next 4K boundary
  for (addr = addr_begin; addr < addr_end; ) {
    if ((addr & 0xffff) == 0 && addr + FLASH_BLOCK_SIZE <= addr_end) {
      FLASH_EraseBlock(addr);
      addr += FLASH_BLOCK_SIZE;
    } else {
      FLASH_EraseSector(addr);
      addr += FLASH_SECTOR_SIZE;
    }
  }
}

void FLASH_ProgramWord(uint32_t addr, uint32_t data)
{
  FLASH_EnableProgram();
  *(volatile uint32_t *)addr = data;
  FLASH_WaitForBusy();
  FLASH_DisableProgram();
}

void FLASH_ProgramHalfWord(uint32_t addr, uint16_t data)
{
  FLASH_EnableProgram();
  *(volatile uint16_t *)addr = data;
  FLASH_WaitForBusy();
  FLASH_DisableProgram();
}

void FLASH_ProgramOptionByte(uint32_t addr, uint8_t data)
{
  FLASH_EnableOptionByteProgram();
  *(uint16_t *)(addr & ~0x1) = (~(uint16_t)data << 8 | data);
  FLASH_WaitForBusy();
  FLASH_DisableProgram();
}

void FLASH_SetFPGAConfigAddress(uint32_t addr)
{
  FLASH_EnableOptionByteProgram();
  FLASH_OB->FPGA_CONFIG = addr;
  FLASH_WaitForBusy();
  FLASH_OB->FPGA_CONFIGn = ~addr;
  FLASH_WaitForBusy();
  FLASH_DisableProgram();
}

void FLASH_StopFastProgram(void)
{
  // In fast program mode, only check for FLASH_SR_BSY flag after FLASH_CR_FASTPG is cleared
  FLASH_DisableProgram();
  FLASH_WaitForBusy();
}

// In fast program mode, the flash controller can take program data continuously without the need to check for 
// FLASH_SR_BSY flag.
void FLASH_FastProgram(uint32_t addr, uint32_t data_buf, int byte_count)
{
  FLASH_EnableFastProgram();
  memcpy((void *)addr, (void *)data_buf, byte_count);
  FLASH_StopFastProgram();
}

void FLASH_FastProgramDMA(uint32_t addr, uint32_t data_buf, int byte_count, DMAC_ChannelNumTypeDef channel)
{
  FLASH_EnableFastProgram();
  if (((addr | data_buf | byte_count) & 0x3) == 0) { // Data and address are word aligned. 32 bit DMA can be used
    DMAC_WaitedTransfer(channel, data_buf, addr, DMAC_ADDR_INCR_ON, DMAC_ADDR_INCR_ON,
                        DMAC_WIDTH_32_BIT, DMAC_WIDTH_32_BIT, DMAC_BURST_256, DMAC_BURST_256,
                        byte_count >> 2, DMAC_MEM_TO_MEM_DMA_CTRL, 0, 0);
  } else {
    DMAC_WaitedTransfer(channel, data_buf, addr, DMAC_ADDR_INCR_ON, DMAC_ADDR_INCR_ON,
                        DMAC_WIDTH_8_BIT, DMAC_WIDTH_8_BIT, DMAC_BURST_256, DMAC_BURST_256,
                        byte_count, DMAC_MEM_TO_MEM_DMA_CTRL, 0, 0);
  }
  // A non-waited DMA with interrupt can be used. In that case FLASH_StopFastProgram() should be called in the ISR
  FLASH_StopFastProgram();
}

void FLASH_EnableReadProtect(void)
{
  FLASH_OB->RDP = 0x0; // Writing any other other value will trigger a full chip erase
}

void FLASH_DisableReadProtect(void)
{
  FLASH_OB->RDP = RDP_WORD; // Will trigger a full chip erase
}

uint32_t FLASH_FlexRead(uint8_t cmd, bool has_addr, uint32_t address, uint8_t data_bytes, uint8_t dummy_bytes)
{
  FLASH->READ_CTRL = (cmd << 0) | (data_bytes << 8) | (dummy_bytes << 16) | (has_addr << 31);
  if (has_addr) {
    FLASH->AR = address;
  }
  FLASH->CR |= FLASH_CR_READ;

  FLASH_Start();
  FLASH_WaitForBusy();
  FLASH->CR &= ~FLASH_CR_READ;
  return FLASH->READ_DATA;
}

uint8_t FLASH_GetManufacturerID()
{
  return FLASH_FlexRead(0x9f, 0, 0, 1, 0);
}

uint32_t FLASH_GetCapacity(void)
{
  uint32_t flash_bits = FLASH_FlexRead(0x5a, 1, 0x34, 4, 1) + 1;
  return flash_bits >> 3; // In bytes
}

void FLASH_GetUniqueID(uint32_t *id)
{
  id[0] = FLASH_FlexRead(0x4b, 0, 0, 4,  4);
  id[1] = FLASH_FlexRead(0x4b, 0, 0, 8,  4);
  id[2] = FLASH_FlexRead(0x4b, 0, 0, 12, 4);
  id[3] = FLASH_FlexRead(0x4b, 0, 0, 16, 4);
}
