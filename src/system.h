#ifndef _AGM_SYSTEM_H
#define _AGM_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

#ifdef AGM_BOARD_INFO_H
#if !__has_include(AGM_BOARD_INFO_H)
#error "Board header is missing. Please run logic or pre-logic to generate."
#endif
#include AGM_BOARD_INFO_H
#endif

#ifndef BOARD_HSI_FREQUENCY
#define BOARD_HSI_FREQUENCY 10000000
#endif

#ifndef BOARD_HSE_FREQUENCY
#define BOARD_HSE_FREQUENCY 8000000
#endif

#ifndef BOARD_PLL_FREQUENCY
#define BOARD_PLL_FREQUENCY 100000000
#endif

#ifndef BOARD_EXT_FREQUENCY
#define BOARD_EXT_FREQUENCY 50000000
#endif

#ifndef BOARD_RTC_FREQUENCY
#define BOARD_RTC_FREQUENCY 32768
#endif


typedef struct
{
  __I  uint32_t BOOT_MODE;     // 0x00, Boot mode from BOOT0 and BOOT1 pins
  __IO uint32_t RST_CNTL;      // 0x04, Reset control register
  __IO uint32_t PWR_CNTL;      // 0x08, Power control register
  __IO uint32_t CLK_CNTL;      // 0x0C, Clock control register
  __IO uint32_t BUS_CNTL;      // 0x10, Bus control register
  __IO uint32_t SWJ_CNTL;      // 0x14, SWJ pin control register
  __IO uint32_t MISC_CNTL;     // 0x18, Miscellaneous control register
  __IO uint32_t DBG_CNTL;      // 0x1C, Debug control register
  __IO uint32_t WKP_RISE_TRG;  // 0x20, Wake up rise triggers
  __IO uint32_t WKP_FALL_TRG;  // 0x24, Wake up fall triggers
  __IO uint32_t WKP_PENDING;   // 0x28, Wake up pending register
       uint32_t RESERVED0;     // 0x2C
  __IO uint32_t MTIME_PSC;     // 0x30, Mtime prescaler value
  __IO uint32_t MTIME_COUNTER; // 0x34, Mtime prescaler counter
  __IO uint32_t PBUS_DIVIDER;  // 0x38, Pbus clock divider
       uint32_t RESERVED1;     // 0x3C
  __IO uint32_t APB_RESET;     // 0x40, APB peripheral reset
       uint32_t RESERVED2[3];  // 0x44-0x4C
  __IO uint32_t AHB_RESET;     // 0x50, AHB peripheral reset
       uint32_t RESERVED3[3];  // 0x54-0x5C
  __IO uint32_t APB_CLKENABLE; // 0x60, APB peripheral clock enable
       uint32_t RESERVED4[3];  // 0x64-0x6C
  __IO uint32_t AHB_CLKENABLE; // 0x70, AHB peripheral clock enable
       uint32_t RESERVED5[3];  // 0x74-0x7C
  __IO uint32_t APB_CLKSTOP;   // 0x80, APB peripheral clock stop during debug
       uint32_t RESERVED6[31]; // 0x84-0xFC
  __I  uint32_t DEVICE_ID;     // 0x100, Device ID code
} SYS_ControlTypeDef;

#define SYSTEMCTRL_BASE (0x03000000)
#define SYS ((SYS_ControlTypeDef *) SYSTEMCTRL_BASE)

#define SYS_RSTF_LPWR   (1 << 31) // Low power reset flag
#define SYS_RSTF_WDOG   (1 << 30) // Watch dog reset flag
#define SYS_RSTF_IWDG   (1 << 29) // IWDG reset flag
#define SYS_RSTF_SFT    (1 << 28) // Software reset flag
#define SYS_RSTF_POR    (1 << 27) // POR reset flag
#define SYS_RSTF_PIN    (1 << 26) // Pin reset flag
#define SYS_RSTF_EXT    (1 << 25) // External reset flag
#define SYS_RST_REMOVE  (1 << 24) // Remove reset flags
#define SYS_RST_FCB_DIS (1 << 2)  // FCB reset disable
#define SYS_RST_EXT_EN  (1 << 1)  // External reset enable
#define SYS_RST_SFT     (1 << 0)  // Software reset

#define SYS_CLK_SOURCE_MASK  0b11
#define SYS_CLK_HSE_ON       (1 << 2) // HSE clock enable
#define SYS_CLK_HSE_BYP      (1 << 3) // HSE clock bypass
#define SYS_CLK_HSE_RDY      (1 << 4) // HSE clock ready
#define SYS_CLK_PLL_ON       (1 << 5) // PLL clock enable
#define SYS_CLK_PLL_RDY      (1 << 6) // PLL clock ready

#define SYS_SCLK_DIV_MASK        0xf
#define SYS_SCLK_DIV_HIGH_OFFSET 8
#define SYS_SCLK_DIV_LOW_OFFSET  12
#define SYS_SCLK_DIV_HIGH(d)     (d << SYS_SCLK_DIV_HIGH_OFFSET)
#define SYS_SCLK_DIV_LOW(d)      (d << SYS_SCLK_DIV_LOW_OFFSET)
#define SYS_SCLK_DIV_HIGH_MASK   SYS_SCLK_DIV_HIGH(SYS_SCLK_DIV_MASK)
#define SYS_SCLK_DIV_LOW_MASK    SYS_SCLK_DIV_LOW(SYS_SCLK_DIV_MASK)

#define SYS_LOWPOWER_MODE_MASK 0b11

#define SYS_SWJ_JTCK_IDX   0
#define SYS_SWJ_JTMS_IDX   1
#define SYS_SWJ_JTDI_IDX   2
#define SYS_SWJ_JTDO_IDX   3
#define SYS_SWJ_NJTRST_IDX 4
#define SYS_SWJ_JTCK       (1 << SYS_SWJ_JTCK_IDX)
#define SYS_SWJ_JTMS       (1 << SYS_SWJ_JTMS_IDX)
#define SYS_SWJ_JTDI       (1 << SYS_SWJ_JTDI_IDX)
#define SYS_SWJ_JTDO       (1 << SYS_SWJ_JTDO_IDX)
#define SYS_SWJ_NJTRST     (1 << SYS_SWJ_NJTRST_IDX)

#define SYS_DBG_STOP      (1 << 1) // Debug stop mode
#define SYS_DBG_STANDBY   (1 << 2) // Debug standby mode
#define SYS_DBG_IWDG_STOP (1 << 3) // Stop IWDG during debug
#define SYS_DBG_RTC_STOP  (1 << 4) // Stop RTC during debug

#define SYS_DBG_NONE 0
#define SYS_DBG_ALL (~0)

#define SYS_MTIME_MASK       0xffff
#define SYS_MTIME_OFF        (1 << 30)
#define SYS_MTIME_DEBUG_STOP (1 << 31)

typedef enum
{
  SYS_BOOT_FLASH  = 0,
  SYS_BOOT_LOADER = 1,
  SYS_BOOT_SRAM   = 3,
} SYS_BootModeTypeDef;

typedef struct
{
  uint32_t HSI_FREQUENCY;
  uint32_t HSE_FREQUENCY;
  uint32_t PLL_FREQUENCY;
  uint32_t EXT_FREQUENCY;
} SYS_ClocksTypeDef;

typedef enum
{
  SYS_CLK_SOURCE_HSI = 0,
  SYS_CLK_SOURCE_HSE = 1,
  SYS_CLK_SOURCE_PLL = 2,
  SYS_CLK_SOURCE_EXT = 3,
} SYS_ClkSourceTypeDef;

typedef enum
{
  SYS_HSE_BYPASS_OFF = 0,
  SYS_HSE_BYPASS_ON  = 1,
  SYS_HSE_NONE = 2,
} SYS_HSE_BypassTypeDef;

typedef enum
{
  SYS_SLEEP_MODE   = 0,
  SYS_STOP_MODE    = 1,
  SYS_STANDBY_MODE = 3,
} SYS_LowPowerTypeDef;

static inline SYS_BootModeTypeDef SYS_GetBootMode(void) { return (SYS->BOOT_MODE & 0x1) ? (SYS_BootModeTypeDef)SYS->BOOT_MODE : SYS_BOOT_FLASH; }

extern SYS_ClocksTypeDef SYS_Clocks;

static inline void SYS_SetHSIFreq(uint32_t freq) { SYS_Clocks.HSI_FREQUENCY = freq; }
static inline void SYS_SetHSEFreq(uint32_t freq) { SYS_Clocks.HSE_FREQUENCY = freq; }
static inline void SYS_SetPLLFreq(uint32_t freq) { SYS_Clocks.PLL_FREQUENCY = freq; }
static inline void SYS_SetEXTFreq(uint32_t freq) { SYS_Clocks.EXT_FREQUENCY = freq; }

static inline uint32_t SYS_GetHSIFreq(void) { return SYS_Clocks.HSI_FREQUENCY; }
static inline uint32_t SYS_GetHSEFreq(void) { return SYS_Clocks.HSE_FREQUENCY; }
static inline uint32_t SYS_GetPLLFreq(void) { return SYS_Clocks.PLL_FREQUENCY; }
static inline uint32_t SYS_GetEXTFreq(void) { return SYS_Clocks.EXT_FREQUENCY; }

uint32_t SYS_GetSysClkFreq(void);
uint32_t SYS_GetPclkFreq(void);

static inline void SYS_SetClkSource(SYS_ClkSourceTypeDef clk_source) { MODIFY_BIT(SYS->CLK_CNTL, SYS_CLK_SOURCE_MASK, clk_source); }
static inline SYS_ClkSourceTypeDef SYS_GetClkSource(void) { return (SYS_ClkSourceTypeDef)(SYS->CLK_CNTL & SYS_CLK_SOURCE_MASK); }

static inline bool SYS_IsHseReady(void) { return SYS->CLK_CNTL & SYS_CLK_HSE_RDY; }
static inline bool SYS_IsPllReady(void) { return SYS->CLK_CNTL & SYS_CLK_PLL_RDY; }

static inline void SYS_EnableHse(void)  { SYS->CLK_CNTL |=  SYS_CLK_HSE_ON; }
static inline void SYS_EnablePll(void)  { SYS->CLK_CNTL |=  SYS_CLK_PLL_ON; }
static inline void SYS_DisableHse(void) { SYS->CLK_CNTL &= ~SYS_CLK_HSE_ON; }
static inline void SYS_DisablePll(void) { SYS->CLK_CNTL &= ~SYS_CLK_PLL_ON; }

void SYS_SwitchHSIClock(void);
void SYS_SwitchHSEClock(SYS_HSE_BypassTypeDef hse_bypass);
void SYS_SwitchPLLClock(SYS_HSE_BypassTypeDef hse_bypass);
__attribute__((weak)) void SYS_SwitchEXTClock(void) { SYS_SetClkSource(SYS_CLK_SOURCE_EXT); } // Can be overridden

static inline void SYS_SetHSIConfig(uint8_t config)    { SYS->MISC_CNTL   = config;  }
static inline void SYS_SetPclkDivider(uint8_t divider) { SYS->PBUS_DIVIDER = divider; }

void SYS_SetSclkDivider(uint8_t divider);
uint8_t SYS_SetSclkAuto(uint32_t freq); // Auto set sclk divider based on frequency
static inline uint8_t SYS_GetSclkDividerHigh(void) { return (SYS->CLK_CNTL >> SYS_SCLK_DIV_HIGH_OFFSET) & SYS_SCLK_DIV_MASK; }
static inline uint8_t SYS_GetSclkDividerLow (void) { return (SYS->CLK_CNTL >> SYS_SCLK_DIV_LOW_OFFSET ) & SYS_SCLK_DIV_MASK; }

static inline uint16_t SYS_GetMtimePrescaler(void) { return SYS->MTIME_PSC & SYS_MTIME_MASK; }
static inline void SYS_SetMtimePrescaler(uint16_t prescaler) { MODIFY_BIT(SYS->MTIME_PSC, SYS_MTIME_MASK, prescaler); }

static inline void SYS_SetMtimeDebugStop(void)   { SYS->MTIME_PSC |=  SYS_MTIME_DEBUG_STOP; }
static inline void SYS_ClearMtimeDebugStop(void) { SYS->MTIME_PSC &= ~SYS_MTIME_DEBUG_STOP; }

static inline void SYS_SetMtimeOff(void) { SYS->MTIME_PSC |=  SYS_MTIME_OFF; }
static inline void SYS_SetMtimeOn(void)  { SYS->MTIME_PSC &= ~SYS_MTIME_OFF; }

static inline void SYS_EnterLowPower(void) { asm("wfi"); }
static inline SYS_LowPowerTypeDef SYS_GetLowPowerMode(void) { return (SYS_LowPowerTypeDef)(SYS->PWR_CNTL & SYS_LOWPOWER_MODE_MASK); }

void SYS_EnterSleepMode(void);
void SYS_EnterStopMode(void);
void SYS_EnterStandbyMode(void);

static inline void SYS_SoftwareReset(void)   { SYS->RST_CNTL |= SYS_RST_SFT; }
static inline void SYS_ClearResetFlags(void) { SYS->RST_CNTL |= SYS_RST_REMOVE; }

static inline bool SYS_IsActiveResetFlag_LPWR(void) { return SYS->RST_CNTL & SYS_RSTF_LPWR; }
static inline bool SYS_IsActiveResetFlag_WDOG(void) { return SYS->RST_CNTL & SYS_RSTF_WDOG; }
static inline bool SYS_IsActiveResetFlag_IWDG(void) { return SYS->RST_CNTL & SYS_RSTF_IWDG; }
static inline bool SYS_IsActiveResetFlag_SFT(void)  { return SYS->RST_CNTL & SYS_RSTF_SFT;  }
static inline bool SYS_IsActiveResetFlag_POR(void)  { return SYS->RST_CNTL & SYS_RSTF_POR;  }
static inline bool SYS_IsActiveResetFlag_PIN(void)  { return SYS->RST_CNTL & SYS_RSTF_PIN;  }
static inline bool SYS_IsActiveResetFlag_EXT(void)  { return SYS->RST_CNTL & SYS_RSTF_EXT;  }

static inline void SYS_EnableExternalReset(void)  { SYS->RST_CNTL |=  SYS_RST_EXT_EN; }
static inline void SYS_DisableExternalReset(void) { SYS->RST_CNTL &= ~SYS_RST_EXT_EN; }

static inline void SYS_DisableFpgaReset(void) { SYS->RST_CNTL |=  SYS_RST_FCB_DIS; }
static inline void SYS_EnableFpgaReset(void)  { SYS->RST_CNTL &= ~SYS_RST_FCB_DIS; }

static inline void SYS_DisableJTCK(void)   { SYS->SWJ_CNTL |= SYS_SWJ_JTCK;   }
static inline void SYS_DisableJTMS(void)   { SYS->SWJ_CNTL |= SYS_SWJ_JTMS;   }
static inline void SYS_DisableJTDI(void)   { SYS->SWJ_CNTL |= SYS_SWJ_JTDI;   }
static inline void SYS_DisableJTDO(void)   { SYS->SWJ_CNTL |= SYS_SWJ_JTDO;   }
static inline void SYS_DisableNJTRST(void) { SYS->SWJ_CNTL |= SYS_SWJ_NJTRST; }

static inline void SYS_EnableJTCK(void)   { SYS->SWJ_CNTL &= ~SYS_SWJ_JTCK;   }
static inline void SYS_EnableJTMS(void)   { SYS->SWJ_CNTL &= ~SYS_SWJ_JTMS;   }
static inline void SYS_EnableJTDI(void)   { SYS->SWJ_CNTL &= ~SYS_SWJ_JTDI;   }
static inline void SYS_EnableJTDO(void)   { SYS->SWJ_CNTL &= ~SYS_SWJ_JTDO;   }
static inline void SYS_EnableNJTRST(void) { SYS->SWJ_CNTL &= ~SYS_SWJ_NJTRST; }

static inline void SYS_EnableAHBClock(uint32_t bits)    { SYS->AHB_CLKENABLE |=  bits; }
static inline void SYS_DisableAHBClock(uint32_t bits)   { SYS->AHB_CLKENABLE &= ~bits; }
static inline bool SYS_IsEnabledAHBClock(uint32_t bits) { return SYS->AHB_CLKENABLE & bits; }

static inline void SYS_EnableAHBReset(uint32_t bits)    { SYS->AHB_RESET |=  bits; }
static inline void SYS_DisableAHBReset(uint32_t bits)   { SYS->AHB_RESET &= ~bits; }
static inline bool SYS_IsEnabledAHBReset(uint32_t bits) { return SYS->AHB_RESET & bits; }
static inline void SYS_AHBReset(uint32_t bits)          { SYS_EnableAHBReset(bits); SYS_DisableAHBReset(bits); }
static inline void SYS_AHBResetAndDisable(uint32_t bits){ SYS_AHBReset(bits); SYS_DisableAHBClock(bits); }

static inline void SYS_EnableAPBClock(uint32_t bits)    { SYS->APB_CLKENABLE |=  bits; }
static inline void SYS_DisableAPBClock(uint32_t bits)   { SYS->APB_CLKENABLE &= ~bits; }
static inline bool SYS_IsEnabledAPBClock(uint32_t bits) { return SYS->APB_CLKENABLE & bits; }

static inline void SYS_EnableAPBReset(uint32_t bits)    { SYS->APB_RESET |=  bits; }
static inline void SYS_DisableAPBReset(uint32_t bits)   { SYS->APB_RESET &= ~bits; }
static inline bool SYS_IsEnabledAPBReset(uint32_t bits) { return SYS->APB_RESET & bits; }
static inline void SYS_APBReset(uint32_t bits)          { SYS_EnableAPBReset(bits); SYS_DisableAPBReset(bits); }
static inline void SYS_APBResetAndDisable(uint32_t bits){ SYS_APBReset(bits); SYS_DisableAPBClock(bits); }

static inline void SYS_EnableAPBClkStop(uint32_t bits)    { SYS->APB_CLKSTOP |=  bits; }
static inline void SYS_DisableAPBClkStop(uint32_t bits)   { SYS->APB_CLKSTOP &= ~bits; }
static inline bool SYS_IsEnabledAPBClkStop(uint32_t bits) { return SYS->APB_CLKSTOP & bits; }

static inline void SYS_EnableDebugConfig(uint32_t bits)  { SYS->DBG_CNTL |=  bits; }
static inline void SYS_DisableDebugConfig(uint32_t bits) { SYS->DBG_CNTL &= ~bits; }

static inline uint32_t SYS_GetDeviceID(void) { return SYS->DEVICE_ID; }

typedef enum
{
  SYS_WAKEUP_EDGE_NONE = 0b00,
  SYS_WAKEUP_EDGE_RISE = 0b01,
  SYS_WAKEUP_EDGE_FALL = 0b10,
  SYS_WAKEUP_EDGE_BOTH = 0b11,
} SYS_WakeupEdgeTypeDef;

// External wake up lines share the same signals with the external interrupts. They do not need interrupt enables to
// work. If the corresponding interrupt is enabled for a wake up signal, the interrupt may be triggered as soon as the
// device wakes up from stop mode. Falling edge wake up can be used to avoid this, because system clock is restored
// after the interrupt becomes inactive (0).
static inline void SYS_SetWakeupEdgeByID(int wakeupID, SYS_WakeupEdgeTypeDef edge)
{
  MODIFY_BIT(SYS->WKP_RISE_TRG, 1 << wakeupID, (edge >> 0 & 0x1) << wakeupID);
  MODIFY_BIT(SYS->WKP_FALL_TRG, 1 << wakeupID, (edge >> 1 & 0x1) << wakeupID);
}
static inline void SYS_SetAlarmWakupEdge(SYS_WakeupEdgeTypeDef edge) { SYS_SetWakeupEdgeByID(SYS_WAKEUP_ALARM_ID, edge); }
static inline bool SYS_ClearPendingWakeups(void) { uint32_t val = SYS->WKP_PENDING; SYS->WKP_PENDING = val; return val; }

#ifdef __cplusplus
}
#endif

#endif
