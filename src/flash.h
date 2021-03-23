#ifndef _AGM_FLASH_H
#define _AGM_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include "dmac.h"

#define FLASH_BASE         (0x80000000)
#define FLASH_OPTION_BASE  (0x81000000)
#define FLASH_OPTION_BYTES (12)
#define FLASH_PAGE_SIZE    (256)
#define FLASH_PAGE_WORDS   (64)
#define FLASH_SECTOR_SIZE  (0x1000)  // 4K
#define FLASH_BLOCK_SIZE   (0x10000) // 64K
#ifndef FLASH_MAX_FREQ
#define FLASH_MAX_FREQ     (100000000) // 100MHz
#endif

typedef struct
{
  __IO uint32_t RESERVED0; // 0x00
  __O  uint32_t KEYR;      // 0x04, Key register
  __O  uint32_t OPTKEYR;   // 0x08, Option byte key register
  __IO uint32_t SR;        // 0x0c, Status register
  __IO uint32_t CR;        // 0x10, Control register
  __IO uint32_t AR;        // 0x14, Address register
  __IO uint32_t RESERVED1; // 0x18
  __I  uint32_t OBR;       // 0x1c, Option byte register
  __I  uint32_t WRPR;      // 0x20, Write protection register
  __I  uint32_t CONFIG;    // 0x24, Configuration register
  __I  uint32_t DMA_DATA;  // 0x28
  __IO uint32_t READ_CTRL; // 0x2c
  __O  uint32_t READ_DATA; // 0x30
} FLASH_TypeDef;

#define FLASH ((FLASH_TypeDef *) 0x40001000)

#define FLASH_SR_BSY      (1 << 0)
#define FLASH_SR_PGERR    (1 << 2)
#define FLASH_SR_WRPRTERR (1 << 4)
#define FLASH_SR_EOP      (1 << 5)

#define FLASH_CR_PG     (1 << 0)
#define FLASH_CR_SER    (1 << 1)
#define FLASH_CR_MER    (1 << 2)
#define FLASH_CR_BER    (1 << 3)
#define FLASH_CR_OPTPG  (1 << 4)
#define FLASH_CR_OPTER  (1 << 5)
#define FLASH_CR_STRT   (1 << 6)
#define FLASH_CR_LOCK   (1 << 7)
#define FLASH_CR_OPTWRE (1 << 9)
#define FLASH_CR_ERRIE  (1 << 10)
#define FLASH_CR_EOPIE  (1 << 12)
#define FLASH_CR_READ   (1 << 14)
#define FLASH_CR_FASTPG (1 << 15)

#define FLASH_OBR_USER_OFFSET   (2)
#define FLASH_OBR_DATA0_OFFSET  (10)
#define FLASH_OBR_DATA1_OFFSET  (18)

#define FLASH_OBR_OPTERR (1    << 0)
#define FLASH_OBR_RDPRT  (1    << 1)
#define FLASH_OBR_USER   (0xff << FLASH_OBR_USER_OFFSET)
#define FLASH_OBR_DATA0  (0xff << FLASH_OBR_DATA0_OFFSET)
#define FLASH_OBR_DATA1  (0xff << FLASH_OBR_DATA1_OFFSET)

#define FLASH_OBR_USER_STDBY_NO_RST (1 << 1)
#define FLASH_OBR_USER_STOP_NO_RST  (1 << 2)

#define RDP_KEY    ((uint8_t)0xA5)
#define RDP_WORD   ((uint16_t)0x5AA5)
#define FLASH_KEY1 ((uint32_t)0x45670123)
#define FLASH_KEY2 ((uint32_t)0xCDEF89AB)

#define FLASH_CR_ERASE_MASK (FLASH_CR_SER | FLASH_CR_MER | FLASH_CR_BER | FLASH_CR_OPTER)
typedef enum {
  FLASH_EraseTypeNone   = 0,
  FLASH_EraseTypeSector = FLASH_CR_SER,
  FLASH_EraseTypeBlock  = FLASH_CR_BER,
  FLASH_EraseTypeChip   = FLASH_CR_MER,
  FLASH_EraseTypeOpt    = FLASH_CR_OPTER,
} FLASH_EraseTypeDef;

typedef struct {
  __IO uint16_t RDP;           // 0x00
  __IO uint16_t USER;          // 0x02
  __IO uint16_t DATA0;         // 0x04
  __IO uint16_t DATA1;         // 0x06
  __IO uint16_t RESERVED0[12]; // 0x08-0x1e
  __IO uint16_t OSC_CONFIG;    // 0x20
  __IO uint16_t OSC_CAL;       // 0x22
  __IO uint16_t RESERVED1[6];  // 0x24-0x2e
  __IO uint32_t FPGA_CONFIG;   // 0x30
  __IO uint32_t FPGA_CONFIGn;  // 0x34
  __IO uint32_t FPGA_COMPRESSED_CONFIG;  // 0x38
  __IO uint32_t FPGA_COMPRESSED_CONFIGn; // 0x3c
  __IO uint32_t RESERVED2[16]; // 0x40-0x7f
} FLASH_OptionByteTypeDef;
#define FLASH_OB ((FLASH_OptionByteTypeDef *) FLASH_OPTION_BASE)

static inline bool FLASH_IsLocked(void)            { return FLASH->CR & FLASH_CR_LOCK;      }
static inline bool FLASH_IsOptionByteLocked(void)  { return !(FLASH->CR & FLASH_CR_OPTWRE); }

static inline void FLASH_EnableProgram(void)           { FLASH->CR |= FLASH_CR_PG;                     }
static inline void FLASH_EnableFastProgram(void)       { FLASH->CR |= (FLASH_CR_PG | FLASH_CR_FASTPG); }
static inline void FLASH_EnableOptionByteProgram(void) { FLASH->CR |= (FLASH_CR_PG | FLASH_CR_OPTPG);  }
static inline void FLASH_DisableProgram(void)          { FLASH->CR &= ~(FLASH_CR_PG | FLASH_CR_FASTPG | FLASH_CR_OPTPG); }

static inline bool FLASH_IsStart(void)              { return FLASH->CR & FLASH_CR_STRT;                 }
static inline bool FLASH_IsProgramEnabled(void)     { return FLASH->CR & FLASH_CR_PG;                   }
static inline bool FLASH_IsFastProgramEnabled(void) { return FLASH->CR & FLASH_CR_PG & FLASH_CR_FASTPG; }

static inline bool FLASH_IsProgramError(void)      { return FLASH->SR & FLASH_SR_PGERR; }
static inline void FLASH_ClearProgramError(void)   { FLASH->SR |= FLASH_SR_PGERR;       }
static inline bool FLASH_IsEndOfOperation(void)    { return FLASH->SR & FLASH_SR_EOP;   }
static inline void FLASH_ClearEndOfOperation(void) { FLASH->SR |= FLASH_SR_EOP;         }

static inline void FLASH_EnableIntError(void)  { FLASH->CR |= FLASH_CR_ERRIE;  }
static inline void FLASH_EnableIntEOP(void)    { FLASH->CR |= FLASH_CR_EOPIE;  }
static inline void FLASH_DisableIntError(void) { FLASH->CR &= ~FLASH_CR_ERRIE; }
static inline void FLASH_DisableIntEOP(void)   { FLASH->CR &= ~FLASH_CR_EOPIE; }

static inline void FLASH_SetEraseMode(FLASH_EraseTypeDef erase_type) { MODIFY_BIT(FLASH->CR, FLASH_CR_ERASE_MASK, erase_type); }
static inline void FLASH_SetAddress(uint32_t addr) { FLASH->AR = addr; }

static inline bool FLASH_IsBusy(void)      { return FLASH->SR & FLASH_SR_BSY; }
static inline void FLASH_WaitForBusy(void) { while (FLASH_IsBusy()); }

static inline bool FLASH_IsOptionByteError(void) { return FLASH->OBR & FLASH_OBR_OPTERR; }
static inline bool FLASH_IsReadProtected(void)   { return FLASH->OBR & FLASH_OBR_RDPRT;  }

static inline uint8_t FLASH_GetOptionByteUser(void)  { return (FLASH->OBR & FLASH_OBR_USER)  >> FLASH_OBR_USER_OFFSET;  }
static inline uint8_t FLASH_GetOptionByteData0(void) { return (FLASH->OBR & FLASH_OBR_DATA0) >> FLASH_OBR_DATA0_OFFSET; }
static inline uint8_t FLASH_GetOptionByteData1(void) { return (FLASH->OBR & FLASH_OBR_DATA1) >> FLASH_OBR_DATA1_OFFSET; }

static inline bool FLASH_IsOptionByteStandbyNoReset(void) { return FLASH_GetOptionByteUser() & FLASH_OBR_USER_STDBY_NO_RST; }
static inline bool FLASH_IsOptionByteStopNoReset(void)    { return FLASH_GetOptionByteUser() & FLASH_OBR_USER_STOP_NO_RST;  }

static inline uint16_t FLASH_MakeOptionByteValue(uint8_t data) { return ((~data) << 8) | data; }

void FLASH_Start(void);
void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_OptionByteUnlock(void);
void FLASH_OptionByteLock(void);

uint32_t FLASH_GetFPGAConfigAddress(void);
uint32_t FLASH_GetFPGACompressedConfigAddress(void);

// All erase and program functions should be called after flash is unlocked
void FLASH_EraseSector(uint32_t addr);
void FLASH_EraseBlock(uint32_t addr);
void FLASH_EraseChip(void);
void FLASH_Erase(uint32_t addr, int byte_count);

void FLASH_ProgramWord(uint32_t addr, uint32_t data);
void FLASH_ProgramHalfWord(uint32_t addr, uint16_t data);
void FLASH_ProgramOptionByte(uint32_t addr, uint8_t data);
void FLASH_SetFPGAConfigAddress(uint32_t addr);

void FLASH_StopFastProgram(void);
void FLASH_FastProgram(uint32_t addr, uint32_t data_buf, int byte_count);
void FLASH_FastProgramDMA(uint32_t addr, uint32_t data_buf, int byte_count, DMAC_ChannelNumTypeDef channel);

// Option byte functions should be called after option byte is unlocked
void FLASH_EraseOptionByte(void);
void FLASH_EnableReadProtect(void);
void FLASH_DisableReadProtect(void);

// All FLASH_FlexRead() based functions should be called after flash is unlocked
uint32_t FLASH_FlexRead(uint8_t cmd, bool has_addr, uint32_t address, uint8_t data_bytes, uint8_t dummy_bytes);
uint8_t FLASH_GetManufacturerID(void);
uint32_t FLASH_GetCapacity(void); // In bytes
void FLASH_GetUniqueID(uint32_t *id);

#ifdef __cplusplus
}
#endif

#endif
