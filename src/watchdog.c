#include "watchdog.h"

void WDOG_Init(uint32_t value)
{
  WDOG_UnLock();
  WDOG->WdogLoad = value;
  WDOG->WdogControl = WDOG_RESET_EN | WDOG_INT_EN;
  WDOG_Lock();
}
