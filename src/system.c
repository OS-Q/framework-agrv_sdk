#include "system.h"
#include "uart.h"
#include "flash.h"

SYS_ClocksTypeDef SYS_Clocks = {
  .HSI_FREQUENCY = BOARD_HSI_FREQUENCY,
  .HSE_FREQUENCY = BOARD_HSE_FREQUENCY,
  .PLL_FREQUENCY = BOARD_PLL_FREQUENCY,
  .EXT_FREQUENCY = BOARD_EXT_FREQUENCY,
};

uint32_t SYS_GetSysClkFreq(void)
{
  switch (SYS->CLK_CNTL & SYS_CLK_SOURCE_MASK) {
  case SYS_CLK_SOURCE_HSI:
    return SYS_Clocks.HSI_FREQUENCY;
  case SYS_CLK_SOURCE_HSE:
    return SYS_Clocks.HSE_FREQUENCY;
  case SYS_CLK_SOURCE_PLL:
    return SYS_Clocks.PLL_FREQUENCY;
  default:
    return SYS_Clocks.EXT_FREQUENCY;
  }
}

uint32_t SYS_GetPclkFreq(void)
{
  return SYS_GetSysClkFreq() / (SYS->PBUS_DIVIDER + 1);
}

void SYS_SwitchHSIClock(void)
{
  SYS->CLK_CNTL &= ~SYS_CLK_SOURCE_MASK;
  SYS->CLK_CNTL &= ~(SYS_CLK_PLL_ON | SYS_CLK_HSE_ON); // Turn off HSE and PLL, must be done after clock source switched to HSI
}

void SYS_SwitchHSEClock(SYS_HSE_BypassTypeDef hse_bypass)
{
  SYS_SwitchHSIClock();
  uint32_t clk_control = SYS->CLK_CNTL;

  // Turn on HSE clock
  clk_control |= SYS_CLK_HSE_ON;
  if (hse_bypass == SYS_HSE_BYPASS_ON) {
    clk_control |= SYS_CLK_HSE_BYP;
  } else {
    clk_control &= ~SYS_CLK_HSE_BYP;
  }
  SYS->CLK_CNTL = clk_control;

  // Wait for HSE ready and switch
  while (!SYS_IsHseReady());
  clk_control |= SYS_CLK_SOURCE_HSE;
  SYS->CLK_CNTL = clk_control;
}

void SYS_SwitchPLLClock(SYS_HSE_BypassTypeDef hse_bypass)
{
  SYS_SwitchHSIClock();
  SYS_SetSclkAuto(SYS_GetPLLFreq()); // Since PLL frequency may exceed FLASH_MAX_FREQ
  uint32_t clk_control = SYS->CLK_CNTL;

  // Turn on PLL clock
  clk_control &= ~SYS_CLK_HSE_BYP;
  switch (hse_bypass) {
  case SYS_HSE_BYPASS_ON:
    clk_control |= SYS_CLK_HSE_BYP;
    // Fall through
  case SYS_HSE_BYPASS_OFF:
    clk_control |= SYS_CLK_HSE_ON;
    // Fall through
  default:
    clk_control |= SYS_CLK_PLL_ON;
    break;
  }
  SYS->CLK_CNTL = clk_control;

  if (clk_control & SYS_CLK_HSE_ON) {
    while (!SYS_IsHseReady());
  }
  uint32_t counter = 0;
  // Wait for PLL ready and switch
  while (!SYS_IsPllReady()) {
    if (++counter > 5000) {
      counter = 0;
      SYS->CLK_CNTL = clk_control & ~SYS_CLK_PLL_ON;
      SYS->CLK_CNTL = clk_control;
    }
  }
  clk_control |= SYS_CLK_SOURCE_PLL;
  SYS->CLK_CNTL = clk_control;
}

void SYS_SetSclkDivider(uint8_t divider)
{
  MODIFY_BIT(SYS->CLK_CNTL, SYS_SCLK_DIV_HIGH_MASK | SYS_SCLK_DIV_LOW_MASK, SYS_SCLK_DIV_HIGH(divider) | SYS_SCLK_DIV_LOW(divider));
}

uint8_t SYS_SetSclkAuto(uint32_t freq)
{
  uint8_t divider = (freq - 1) / FLASH_MAX_FREQ;
  SYS_SetSclkDivider(divider);
  return divider;
}

void SYS_EnterSleepMode(void)
{
  MODIFY_BIT(SYS->PWR_CNTL, SYS_LOWPOWER_MODE_MASK, SYS_SLEEP_MODE);
  SYS_EnterLowPower();
}

void SYS_EnterStopMode(void)
{
  MODIFY_BIT(SYS->PWR_CNTL, SYS_LOWPOWER_MODE_MASK, SYS_STOP_MODE);
  SYS_SwitchHSIClock();
  SYS_EnterLowPower();
}

void SYS_EnterStandbyMode(void)
{
  MODIFY_BIT(SYS->PWR_CNTL, SYS_LOWPOWER_MODE_MASK, SYS_STANDBY_MODE);
  SYS_SwitchHSIClock();
  SYS_EnterLowPower();
}
