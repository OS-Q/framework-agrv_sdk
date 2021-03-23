#ifndef _AGM_IWDG_H
#define _AGM_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include "rtc.h"

#define IWDG_ENABLE         (1 << 8)
#define IWDG_STOP_FREEZE    (1 << 4)
#define IWDG_STANDBY_FREEZE (1 << 5)
#define IWDG_CLKSEL         (1 << 6)

#define IWDG_PRESCALER_MASK 0x7
#define IWDG_RELOAD_MASK    0xf000
#define IWDG_RELOAD_KEY     0xa000

typedef enum
{
  IWDG_FREEZE_NONE    = 0,
  IWDG_FREEZE_STOP    = IWDG_STOP_FREEZE,
  IWDG_FREEZE_STANDBY = IWDG_STANDBY_FREEZE,
  IWDG_FREEZE_ALL     = IWDG_STOP_FREEZE | IWDG_STANDBY_FREEZE,
} IWDG_FreezeTypeDef;
#define IWDG_FREEZE_MASK (IWDG_STOP_FREEZE | IWDG_STANDBY_FREEZE)

typedef enum
{
  IWDG_CLK_SOURCE_LSI = 0,
  IWDG_CLK_SOURCE_LSE = IWDG_CLKSEL,
} IWDG_ClkSourceTypeDef;

static inline bool IWDG_IsEnabled(void)                 { return RTC->IWDG & IWDG_ENABLE; }
static inline void IWDG_Enable(void)                    { RTC_MODIFY_BIT(RTC->IWDG, IWDG_ENABLE, IWDG_ENABLE); }
static inline void IWDG_Disable(void)                   { RTC_MODIFY_BIT(RTC->IWDG, IWDG_ENABLE, 0); }
static inline void IWDG_SetPrescaler(uint8_t prescaler) { RTC_MODIFY_BIT(RTC->IWDG, IWDG_PRESCALER_MASK, prescaler); }
static inline void IWDG_ReloadCounter(void)             { RTC_MODIFY_BIT(RTC->IWDG, IWDG_RELOAD_MASK, IWDG_RELOAD_KEY); }
static inline void IWDG_SetFreezeMode(IWDG_FreezeTypeDef mode) { RTC_MODIFY_BIT(RTC->IWDG, IWDG_FREEZE_MASK, mode); }

// Clk source is always LSE in standby mode
static inline void IWDG_SetClkSource(IWDG_ClkSourceTypeDef clk_source) { RTC_MODIFY_BIT(RTC->IWDG, IWDG_CLKSEL, clk_source); }

#ifdef __cplusplus
}
#endif

#endif
