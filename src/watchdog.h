#ifndef _AGM_WDOG_H
#define _AGM_WDOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include "system.h"

typedef struct
{
  __IO uint32_t WdogLoad;    // 0x00, Load Register
  __I  uint32_t WdogValue;   // 0x04, Value Register
  __IO uint32_t WdogControl; // 0x08, Control register
  __O  uint32_t WdogIntClr;  // 0x0C, Interrupt Clear Register
  __I  uint32_t WdogRIS;     // 0x10, Raw Interrupt Status Register
  __I  uint32_t WdogMIS;     // 0x14, Masked Interrupt Status Register
  __IO uint32_t RESERVED[762];
  __IO uint32_t WdogLock;    // 0xC00, Lock Register
} WATCHDOG_TypeDef;
#define WDOG WATCHDOG0 // This is the only WATCHDOG supported for now

#define WDOG_INT_EN   (1 << 0)
#define WDOG_RESET_EN (1 << 1)

static inline void WDOG_Lock(void)   { WDOG->WdogLock = 0;          }
static inline void WDOG_UnLock(void) { WDOG->WdogLock = 0x1ACCE551; }

static inline uint32_t WDOG_GetLoad(void)  { return WDOG->WdogLoad; }
static inline uint32_t WDOG_GetValue(void) { return WDOG->WdogValue; }

// Clearing the interrupt will also reload WdogValue with WdogLoad
static inline void WDOG_ClearInt(void) { WDOG_UnLock(); WDOG->WdogIntClr = 1; WDOG_Lock(); }

void WDOG_Init(uint32_t value);

static inline void WDOG_Feed(void)   { WDOG_ClearInt(); }
static inline void WDOG_Init1S(void) { WDOG_Init(SYS_GetPclkFreq()); } // Initial for 1 second delay
static inline void WDOG_InitMS(uint32_t ms) { WDOG_Init(SYS_GetPclkFreq() / 1000 * ms); } // Initial for millisecond delay

#ifdef __cplusplus
}
#endif

#endif
