#include "timer.h"
#include "system.h"

void TIM_Init1(TIMER_TypeDef *tim, uint32_t timeInUs, TIMER_ModeTypeDef mode)
{
  tim->Timer1Load = SYS_GetPclkFreq() / 1000000 * timeInUs;
  tim->Timer1Ctrl = mode | TIMER_SIZE_32 | TIMER_PRESCALE_1 | TIMER_CTRL_INT_EN | TIMER_CTRL_ENABLE;
}

void TIM_Init2(TIMER_TypeDef *tim, uint32_t timeInUs, TIMER_ModeTypeDef mode)
{
  tim->Timer2Load = SYS_GetPclkFreq() / 1000000 * timeInUs;
  tim->Timer2Ctrl = mode | TIMER_SIZE_32 | TIMER_PRESCALE_1 | TIMER_CTRL_INT_EN | TIMER_CTRL_ENABLE;
}

