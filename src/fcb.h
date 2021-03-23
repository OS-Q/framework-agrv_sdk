#ifndef _AGM_FCB_H
#define _AGM_FCB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include "dmac.h"

#define FCB FCB0 // This is the only FCB supported

// To store the config address of FPGA bit stream and it's complement value
#define FPGA_CONFIG_ADDR   0x81000030
#define FPGA_CONFIG_ADDR_N 0x81000034

#define FCB_CTRL_INIT       (1 << 0)
#define FCB_CTRL_WRITE      (1 << 1)
#define FCB_CTRL_READ       (1 << 2)
#define FCB_CTRL_UPDATE     (1 << 3)
#define FCB_CTRL_ACTIVATE   (1 << 4)
#define FCB_CTRL_DEACTIVATE (1 << 5)
#define FCB_CTRL_AUTO       (1 << 6)
#define FCB_CTRL_DMA        (1 << 7)

#define FCB_STAT_INIT       (1 << 0)
#define FCB_STAT_ACTIVE     (1 << 1)
#define FCB_STAT_ERR_ID     (1 << 4)
#define FCB_STAT_ERR_HEADER (1 << 5)
#define FCB_STAT_ERR_CRC    (1 << 6)
#define FCB_STAT_ERR_ALL (FCB_STAT_ERR_ID | FCB_STAT_ERR_HEADER | FCB_STAT_ERR_CRC)

#define FCB_AUTO_WORDS     (99944 / 4)

typedef struct
{
  __IO uint32_t CTRL; // 0x00
  __IO uint32_t ADDR; // 0x04
  __IO uint32_t DATA; // 0x08
  __IO uint32_t AUTO; // 0x0c
  __IO uint32_t STAT; // 0x10
  __IO uint32_t INT;  // 0x14
} FCB_TypeDef;

// The non-error bits in STAT register are read only. The error bits are cleared by writing 1.
static inline bool FCB_IsInit(void)        { return FCB->STAT & FCB_STAT_INIT;       }
static inline bool FCB_IsActive(void)      { return FCB->STAT & FCB_STAT_ACTIVE;     }
static inline bool FCB_IsErrorID(void)     { return FCB->STAT & FCB_STAT_ERR_ID;     }
static inline bool FCB_IsErrorHeader(void) { return FCB->STAT & FCB_STAT_ERR_HEADER; }
static inline bool FCB_IsErrorCrc(void)    { return FCB->STAT & FCB_STAT_ERR_CRC;    }
static inline bool FCB_IsAnyError(void)    { return FCB->STAT & FCB_STAT_ERR_ALL;    }
static inline void FCB_ClearErrors(void)   { FCB->STAT = FCB_STAT_ERR_ALL; }

static inline void FCB_EnableInt(uint32_t bits)  { FCB->INT |=  bits; }
static inline void FCB_DisableInt(uint32_t bits) { FCB->INT &= ~bits; }
static inline void FCB_ClearInt(void)            { FCB->INT = 0; FCB_ClearErrors(); }

static inline void FCB_Activate(void)   { FCB->CTRL |= FCB_CTRL_ACTIVATE;   }
static inline void FCB_DeActivate(void) { FCB->CTRL |= FCB_CTRL_DEACTIVATE; }

ReturnCodeTypedef FCB_AutoConfig(uint32_t config_addr);
ReturnCodeTypedef FCB_AutoConfigDma(uint32_t config_addr, DMAC_ChannelNumTypeDef channel);
ReturnCodeTypedef FCB_AutoDecompressEncrypt(uint32_t config_addr, uint8_t(*encrypt_decode)(uint8_t));
static inline ReturnCodeTypedef FCB_AutoDecompress(uint32_t config_addr)
{
  return FCB_AutoDecompressEncrypt(config_addr, NULL);
}

#define FCB_IO_ADDR  0x400
#define FCB_IO_WORDS 27

#define FCB_PLL_ADDR  0x401
#define FCB_PLL_WORDS 8

typedef struct
{
  union {
    uint8_t BYTES[2];
    struct {
      uint32_t RESERVED0    : 5;
      uint32_t CFG_RESSEL   : 2;
      uint32_t CFG_RCOSCCAL : 7;
      uint32_t CFG_RCOSC_EN : 1;
    };
  };
} FCB_OSC_TypeDef;

typedef struct
{
  union {
    uint32_t WORDS[FCB_IO_WORDS];
    struct {
      uint8_t RESERVED0[52];
      uint8_t RC_OSC[2];
    };
  };
} FCB_IO_TypeDef;

typedef struct
{
  union {
    uint32_t WORDS[FCB_PLL_WORDS];
    uint8_t  BYTES[FCB_PLL_WORDS * 4];
    struct __attribute__((packed)) __attribute__((aligned(4))) {
      uint32_t REG_CTRL        : 2;
      uint32_t PLL_EN_FLAG     : 1;
      uint32_t FEEDBACK_MODE1  : 2;
      uint32_t FBDELAY_VAL     : 3;
      uint32_t PllClkInMUX     : 6;
      uint32_t PllSeamMUX      : 3;
      uint32_t FEEDBACK_MODE0  : 1;
      uint32_t PLLOUTN_EN      : 1;
      uint32_t PLLOUTP_EN      : 1;
      uint32_t CLKFB_PHASE     : 3;
      uint32_t CLKFB_DEL       : 8;
      uint32_t CLKOUT0_PHASE   : 3;
      uint32_t CLKDIV0_EN      : 1;
      uint32_t CLKOUT0_DEL     : 8;
      uint32_t CLKOUT1_CASCADE : 1;
      uint32_t CLKOUT1_PHASE   : 3;
      uint32_t CLKDIV1_EN      : 1;
      uint32_t CLKOUT1_DEL     : 8;
      uint32_t CLKOUT2_CASCADE : 1;
      uint32_t CLKOUT2_PHASE   : 3;
      uint32_t CLKDIV2_EN      : 1;
      uint32_t CLKOUT2_DEL     : 8;
      uint32_t CLKOUT3_CASCADE : 1;
      uint32_t CLKOUT3_PHASE   : 3;
      uint32_t CLKDIV3_EN      : 1;
      uint32_t CLKOUT3_DEL     : 8;
      uint32_t CLKOUT4_CASCADE : 1;
      uint32_t CLKOUT4_PHASE   : 3;
      uint32_t CLKDIV4_EN      : 1;
      uint32_t CLKOUT4_DEL     : 8;
      uint32_t CLKOUT4_LOW     : 8;
      uint32_t CLKOUT4_TRIM    : 1;
      uint32_t CLKOUT4_HIGH    : 8;
      uint32_t CLKOUT4_BYPASS  : 1;
      uint32_t CLKOUT3_LOW     : 8;
      uint32_t CLKOUT3_TRIM    : 1;
      uint32_t CLKOUT3_HIGH    : 8;
      uint32_t CLKOUT3_BYPASS  : 1;
      uint32_t CLKOUT2_LOW     : 8;
      uint32_t CLKOUT2_TRIM    : 1;
      uint32_t CLKOUT2_HIGH    : 8;
      uint32_t CLKOUT2_BYPASS  : 1;
      uint32_t CLKOUT1_LOW     : 8;
      uint32_t CLKOUT1_TRIM    : 1;
      uint32_t CLKOUT1_HIGH    : 8;
      uint32_t CLKOUT1_BYPASS  : 1;
      uint32_t CLKOUT0_LOW     : 8;
      uint32_t CLKOUT0_TRIM    : 1;
      uint32_t CLKOUT0_HIGH    : 8;
      uint32_t CLKOUT0_BYPASS  : 1;
      uint32_t CLKFB_LOW       : 8;
      uint32_t CLKFB_TRIM      : 1;
      uint32_t CLKFB_HIGH      : 8;
      uint32_t CLKFB_BYPASS    : 1;
      uint32_t CLKIN_LOW       : 8;
      uint32_t CLKIN_TRIM      : 1;
      uint32_t CLKIN_HIGH      : 8;
      uint32_t CLKIN_BYPASS    : 1;
      uint32_t CP              : 3;
      uint32_t DUMMY           : 5;
      uint32_t VCO_POST_DIV    : 1;
      uint32_t RLPF            : 2;
      uint32_t RREF            : 2;
      uint32_t RVI             : 2;
      uint32_t IVCO            : 3;
    };
  };
} FCB_PLL_Typedef;

void FCB_ReadIOConfig(FCB_IO_TypeDef *io_cfg);
void FCB_WriteIOConfig(FCB_IO_TypeDef *io_cfg);
void FCB_SetOscConfig(FCB_IO_TypeDef *io_cfg, FCB_OSC_TypeDef *osc_cfg);
void FCB_GetOscConfig(FCB_IO_TypeDef *io_cfg, FCB_OSC_TypeDef *osc_cfg);

void FCB_ReadPLLConfig(FCB_PLL_Typedef *pll_cfg);
void FCB_WritePLLConfig(FCB_PLL_Typedef *pll_cfg);

#ifdef __cplusplus
}
#endif

#endif
