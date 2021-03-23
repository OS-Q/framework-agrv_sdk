#ifndef _AGM_SPI_H
#define _AGM_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include "dmac.h"

typedef struct __attribute__ ((aligned (4096)))
{
  __IO uint32_t CTRL;          // 0x00, Control Register
  __IO uint32_t RESERVED[3];   // 0x04-0x0C
  __IO uint32_t PHASE_CTRL[8]; // 0x10-0x2C, Phase Control Register
  __IO uint32_t PHASE_DATA[8]; // 0x30-0x4C, Phase Data Register
} SPI_TypeDef;

#define SPI_CTRL_START     (1 << 0)
#define SPI_CTRL_DONE      (1 << 1)
#define SPI_CTRL_ERROR     (1 << 2)
#define SPI_CTRL_INT_CLR   (1 << 3)
#define SPI_CTRL_DMA_EN    (1 << 8)
#define SPI_CTRL_WP_EN     (1 << 9)
#define SPI_CTRL_ENDIAN    (1 << 10)
#define SPI_CTRL_INT_EN    (1 << 20)
#define SPI_CTRL_RESET     (1 << 31)

#define SPI_CTRL_SCLK_DIV_OFFSET 12
#define SPI_CTRL_SCLK_DIV_MASK   (0xff << SPI_CTRL_SCLK_DIV_OFFSET)

#define SPI_CTRL_PHASE_CNT_OFFSET 4
#define SPI_CTRL_PHASE_CNT_MASK  (0x7 << SPI_CTRL_PHASE_CNT_OFFSET)

#define SPI_PHASE_START  (1 << 0)
#define SPI_PHASE_DONE   (1 << 1)
#define SPI_PHASE_ERROR  (1 << 2)
#define SPI_PHASE_ACTION (3 << 4)
#define SPI_PHASE_MODE   (3 << 20)

#define SPI_PHASE_BYTE_CNT_OFFSET 8
#define SPI_PHASE_BYTE_CNT_MASK   (0xfff << SPI_PHASE_BYTE_CNT_OFFSET)
#define SPI_PHASE_BYTE_CNT_MAX    (0x1000 - 4)

#ifndef SPI_RX_PIPELINE
#define SPI_RX_PIPELINE 0
#endif

typedef enum
{
  SPI_CTRL_PHASE_CNT1 = (0 << 4),
  SPI_CTRL_PHASE_CNT2 = (1 << 4),
  SPI_CTRL_PHASE_CNT3 = (2 << 4),
  SPI_CTRL_PHASE_CNT4 = (3 << 4),
  SPI_CTRL_PHASE_CNT5 = (4 << 4),
  SPI_CTRL_PHASE_CNT6 = (5 << 4),
  SPI_CTRL_PHASE_CNT7 = (6 << 4),
  SPI_CTRL_PHASE_CNT8 = (7 << 4),
} SPI_PhaseCntTypeDef;

typedef enum
{
  SPI_CTRL_DMA_OFF = 0,
  SPI_CTRL_DMA_ON  = SPI_CTRL_DMA_EN,
} SPI_DmaTypeDef;

typedef enum
{
  SPI_INTERRUPT_OFF= 0,
  SPI_INTERRUPT_ON = SPI_CTRL_INT_EN,
} SPI_InterruptTypeDef;

typedef enum
{
  SPI_CTRL_BIG_ENDIAN    = (0 << 10),
  SPI_CTRL_LITTLE_ENDIAN = (1 << 10),
} SPI_EndianTypeDef;

typedef enum
{
  SPI_CTRL_SCLK_DIV2   = (2   << SPI_CTRL_SCLK_DIV_OFFSET),
  SPI_CTRL_SCLK_DIV4   = (4   << SPI_CTRL_SCLK_DIV_OFFSET),
  SPI_CTRL_SCLK_DIV8   = (8   << SPI_CTRL_SCLK_DIV_OFFSET),
  SPI_CTRL_SCLK_DIV16  = (16  << SPI_CTRL_SCLK_DIV_OFFSET),
  SPI_CTRL_SCLK_DIV32  = (32  << SPI_CTRL_SCLK_DIV_OFFSET),
  SPI_CTRL_SCLK_DIV64  = (64  << SPI_CTRL_SCLK_DIV_OFFSET),
  SPI_CTRL_SCLK_DIV128 = (128 << SPI_CTRL_SCLK_DIV_OFFSET),
  SPI_CTRL_SCLK_DIV256 = (0   << SPI_CTRL_SCLK_DIV_OFFSET),
} SPI_SclkDivTypeDef;

typedef enum
{
  SPI_PHASE_ACTION_TX       = (0 << 4),
  SPI_PHASE_ACTION_DUMMY_TX = (1 << 4),
  SPI_PHASE_ACTION_RX       = (2 << 4),
  SPI_PHASE_ACTION_POLL     = (3 << 4),
} SPI_PhaseActionTypeDef;

typedef enum
{
  SPI_PHASE_MODE_SINGLE = (0 << 20),
  SPI_PHASE_MODE_DUAL   = (1 << 20),
  SPI_PHASE_MODE_QUAD   = (2 << 20),
} SPI_PhaseModeTypeDef;

typedef enum
{
  SPI_PHASE_0 = 0,
  SPI_PHASE_1 = 1,
  SPI_PHASE_2 = 2,
  SPI_PHASE_3 = 3,
  SPI_PHASE_4 = 4,
  SPI_PHASE_5 = 5,
  SPI_PHASE_6 = 6,
  SPI_PHASE_7 = 7,
} SPI_PhaseNumberTypeDef;

static inline uint32_t SPI_RX_DMA_REQ(SPI_TypeDef *spi) { return (spi == SPI0) ? SPI0_RX_DMA_REQ : SPI1_RX_DMA_REQ; }
static inline uint32_t SPI_TX_DMA_REQ(SPI_TypeDef *spi) { return (spi == SPI0) ? SPI0_TX_DMA_REQ : SPI1_TX_DMA_REQ; }

static inline void SPI_Reset(SPI_TypeDef *spi) { spi->CTRL |= SPI_CTRL_RESET; spi->CTRL &= ~SPI_CTRL_RESET; }
static inline void SPI_Start(SPI_TypeDef *spi, SPI_PhaseCntTypeDef phase_cnt, SPI_DmaTypeDef dma, SPI_InterruptTypeDef interrupt)
{ // Bits to be modified in CTRL: START, PHASE_CNT, DMA_EN, INT_EN
  // Bits not changed: WP_EN, ENDIAN, SCLK_DIV
  MODIFY_BIT(spi->CTRL, SPI_CTRL_PHASE_CNT_MASK | SPI_CTRL_DMA_EN | SPI_CTRL_INT_EN, SPI_CTRL_START | dma | phase_cnt | interrupt);
}

static inline bool SPI_IsDone (SPI_TypeDef *spi)  { return spi->CTRL & SPI_CTRL_DONE; }
static inline bool SPI_IsError(SPI_TypeDef *spi)  { return spi->CTRL & SPI_CTRL_ERROR; }
static inline void SPI_WaitForDone(SPI_TypeDef *spi ) { while (!SPI_IsDone(spi)); }

// DMA only applies to the last phase when phase count is more than 1
static inline void SPI_EnableDMA(SPI_TypeDef *spi)  { spi->CTRL |=  SPI_CTRL_DMA_EN; }
static inline void SPI_DisableDMA(SPI_TypeDef *spi) { spi->CTRL &= ~SPI_CTRL_DMA_EN; }

static inline void SPI_EnableInt(SPI_TypeDef *spi)    { spi->CTRL |=  SPI_CTRL_INT_EN; }
static inline void SPI_DisableInt(SPI_TypeDef *spi)   { spi->CTRL &= ~SPI_CTRL_INT_EN; }
static inline void SPI_ClearInt(SPI_TypeDef *spi)     { spi->CTRL |=  SPI_CTRL_INT_CLR; }
static inline bool SPI_IsEnabledInt(SPI_TypeDef *spi) { return spi->CTRL & SPI_CTRL_INT_EN;  }
static inline bool SPI_IsIntActive(SPI_TypeDef *spi)  { return spi->CTRL & SPI_CTRL_INT_CLR; }

static inline void SPI_SetPhaseCtrl(SPI_TypeDef *spi, SPI_PhaseNumberTypeDef phase, SPI_PhaseActionTypeDef action,
                                    SPI_PhaseModeTypeDef mode, uint32_t byte_cnt)
{
  spi->PHASE_CTRL[phase] = action | mode | ((byte_cnt << SPI_PHASE_BYTE_CNT_OFFSET) & SPI_PHASE_BYTE_CNT_MASK);
}
static inline void SPI_SetPhaseData(SPI_TypeDef *spi, SPI_PhaseNumberTypeDef phase, uint32_t data)
{
  spi->PHASE_DATA[phase] = data;
}
static inline uint32_t SPI_GetPhaseData(SPI_TypeDef *spi, SPI_PhaseNumberTypeDef phase)
{
  return spi->PHASE_DATA[phase];
}

void SPI_Init(SPI_TypeDef *spi, SPI_SclkDivTypeDef div);

// Commonly used functions for single mode
void SPI_Send(SPI_TypeDef *spi, int tx_bytes, const uint32_t tx_data);
void SPI_SendDMA(SPI_TypeDef *spi, int tx_bytes, const uint32_t *tx_data, DMAC_ChannelNumTypeDef channel);
uint32_t SPI_SendAndReceive(SPI_TypeDef *spi, int tx_bytes, const uint32_t tx_data, int rx_bytes);
void SPI_SendAndReceiveDMA(SPI_TypeDef *spi, int tx_bytes, const uint32_t *tx_data,
                           int rx_bytes, uint32_t *rx_data, DMAC_ChannelNumTypeDef channel);


// SPI Flash functions

#define SPI_FLASH_PAGE_SIZE   0x100
#define SPI_FLASH_SECTOR_SIZE 0x1000
#define SPI_FLASH_BLOCK_SIZE  0x10000

#define SPI_FLASH_PAGE_MASK   ((uint32_t)(-SPI_FLASH_PAGE_SIZE))
#define SPI_FLASH_SECTOR_MASK ((uint32_t)(-SPI_FLASH_SECTOR_SIZE))
#define SPI_FLASH_BLOCK_MASK  ((uint32_t)(-SPI_FLASH_BLOCK_SIZE))

// SPI flash takes address bytes in reversed order
#define SPI_FLASH_ADDR(__ADDR) (((__ADDR & 0xff) << 16) | (__ADDR & 0xff00) | ((__ADDR & 0xff0000) >> 16))
#define SPI_FLASH_CMD_ADDR(__CMD, __ADDR) (__CMD | (SPI_FLASH_ADDR(__ADDR) << SPI_PHASE_BYTE_CNT_OFFSET))

#define SPI_FLASH_CMD_PP    0x02 // Page Program
#define SPI_FLASH_CMD_DPP   0xA2 // Dual Page Program
#define SPI_FLASH_CMD_QPP   0x32 // Quad Page Program
#define SPI_FLASH_CMD_WRSR  0x01 // Write Status Register
#define SPI_FLASH_CMD_WREN  0x06 // Write enable
#define SPI_FLASH_CMD_WRDIS 0x04 // Write Disable
#define SPI_FLASH_CMD_READ  0x03 // Read from Memory
#define SPI_FLASH_CMD_FREAD 0x0B // Fast read
#define SPI_FLASH_CMD_DREAD 0x3B // Dual read
#define SPI_FLASH_CMD_2READ 0xBB // Dual read 2x IO
#define SPI_FLASH_CMD_QREAD 0x6B // Quad read
#define SPI_FLASH_CMD_4READ 0xEB // Quad read 4x IO
#define SPI_FLASH_CMD_RDSR  0x05 // Read Status Register S0-S7
#define SPI_FLASH_CMD_RDSR2 0x35 // Read Status Register S8-S15
#define SPI_FLASH_CMD_SE    0x20 // Sector Erase (4K)
#define SPI_FLASH_CMD_BE    0xD8 // Block Erase (64K)
#define SPI_FLASH_CMD_CE    0xC7 // Chip Erase
#define SPI_FLASH_CMD_RDID  0x9F // Read ID
#define SPI_FLASH_CMD_REMS  0x90 // Read Manufacturer ID
#define SPI_FLASH_CMD_RDUID 0x4B // Read unique ID
#define SPI_FLASH_CMD_DP    0xB9 // Deep Power-down
#define SPI_FLASH_CMD_RDP   0xAB // Release Deep Power-down and Read Electronic ID
#define SPI_FLASH_CMD_SFDP  0x5A // Enter SFDP read mode

#define SPI_FLASH_WIP_FLAG   (1 << 0) // Write In Progress (WIP) flag
#define SPI_FLASH_QE_FLAG    (1 << 9) // Quad Enable flag

#define SPI_FLASH_Init SPI_Init

void SPI_FLASH_SetCmdPhase(SPI_TypeDef *spi, uint32_t cmd);
void SPI_FLASH_SetCmdAddrPhase(SPI_TypeDef *spi, uint32_t cmd, uint32_t addr);
void SPI_FLASH_SingleCmd(SPI_TypeDef *spi, uint32_t cmd);
void SPI_FLASH_SingleCmdAddr(SPI_TypeDef *spi, uint32_t cmd, uint32_t addr);
void SPI_FLASH_WaitForWrite(SPI_TypeDef *spi, SPI_InterruptTypeDef interrupt);

static inline void SPI_FLASH_WriteEnable (SPI_TypeDef *spi) { SPI_FLASH_SingleCmd(spi, SPI_FLASH_CMD_WREN); }
static inline void SPI_FLASH_WriteDisable(SPI_TypeDef *spi) { SPI_FLASH_SingleCmd(spi, SPI_FLASH_CMD_WRDIS); }
static inline void SPI_FLASH_PowerDown   (SPI_TypeDef *spi) { SPI_FLASH_SingleCmd(spi, SPI_FLASH_CMD_DP); }

void SPI_FLASH_ReadUniqueID(SPI_TypeDef *spi, uint32_t *uid, DMAC_ChannelNumTypeDef channel);
uint32_t SPI_FLASH_ReadID(SPI_TypeDef *spi);
uint32_t SPI_FLASH_ReadManufacturerID(SPI_TypeDef *spi);
uint32_t SPI_FLASH_GetCapacity(SPI_TypeDef *spi);
uint32_t SPI_FLASH_ReleaseDP(SPI_TypeDef *spi);
uint16_t SPI_FLASH_ReadStatus(SPI_TypeDef *spi);
void     SPI_FLASH_WriteStatus(SPI_TypeDef *spi, uint16_t status);
void     SPI_FLASH_QuadEnable(SPI_TypeDef *spi);
void     SPI_FLASH_QuadDisable(SPI_TypeDef *spi);

// If interrupt is set to SPI_INTERRUPT_OFF, these functions will wait until the operation is finished. If interrupt is
// set to SPI_INTERRUPT_ON, functions will return right after the operation is setup, and an interrupt will be triggered
// at the end of operation.
void SPI_FLASH_EraseSector(SPI_TypeDef *spi, uint32_t addr, SPI_InterruptTypeDef interrupt);
void SPI_FLASH_EraseBlock(SPI_TypeDef *spi, uint32_t addr, SPI_InterruptTypeDef interrupt);
void SPI_FLASH_EraseChip(SPI_TypeDef *spi, SPI_InterruptTypeDef interrupt);
void SPI_FLASH_WritePage(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, uint32_t length, SPI_PhaseModeTypeDef mode,
                         DMAC_ChannelNumTypeDef channel, SPI_InterruptTypeDef interrupt);
void SPI_FLASH_ReadSector(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, uint32_t length, SPI_PhaseModeTypeDef mode,
                          DMAC_ChannelNumTypeDef channel, SPI_InterruptTypeDef interrupt);

// Total size must be 4-byte aligned
void SPI_FLASH_Erase(SPI_TypeDef *spi, uint32_t addr, int total);
void SPI_FLASH_Write(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, int total, SPI_PhaseModeTypeDef mode, DMAC_ChannelNumTypeDef channel);
void SPI_FLASH_Read(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, int total, SPI_PhaseModeTypeDef mode, DMAC_ChannelNumTypeDef channel);

// SPI PSRAM functions

#define SPI_PSRAM_PAGE_SIZE 1024
#define SPI_PSRAM_PAGE_MASK ((uint32_t)(-SPI_PSRAM_PAGE_SIZE))

#define SPI_PSRAM_CMD_QPI_EN  0x35
#define SPI_PSRAM_CMD_QPI_DIS 0xf5
#define SPI_PSRAM_CMD_WRITE   0x02
#define SPI_PSRAM_CMD_QWRITE  0x38
#define SPI_PSRAM_CMD_READ    0x0B
#define SPI_PSRAM_CMD_QREAD   0xEB

void SPI_PRAM_EnableQPI(SPI_TypeDef *spi);
void SPI_PRAM_DisableQPI(SPI_TypeDef *spi);
void SPI_PSRAM_WritePage(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, uint32_t length, SPI_PhaseModeTypeDef mode,
                         DMAC_ChannelNumTypeDef channel, SPI_InterruptTypeDef interrupt, bool qpi_mode);
void SPI_PSRAM_ReadPage(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, uint32_t length, SPI_PhaseModeTypeDef mode,
                        DMAC_ChannelNumTypeDef channel, SPI_InterruptTypeDef interrupt, bool qpi_mode);
void SPI_PSRAM_Write(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, int total, SPI_PhaseModeTypeDef mode,
                     DMAC_ChannelNumTypeDef channel, bool qpi_mode);
void SPI_PSRAM_Read(SPI_TypeDef *spi, uint32_t *buf, uint32_t addr, int total, SPI_PhaseModeTypeDef mode,
                    DMAC_ChannelNumTypeDef channel, bool qpi_mode);

#ifdef __cplusplus
}
#endif

#endif
