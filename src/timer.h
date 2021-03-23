#ifndef _AGM_TIMER_H
#define _AGM_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

typedef struct
{
  __IO uint32_t Timer1Load;   // 0x00, Load Register
  __I  uint32_t Timer1Value;  // 0x04, Current Value Register
  __IO uint32_t Timer1Ctrl;   // 0x08, Control Register
  __O  uint32_t Timer1IntClr; // 0x0C, Interrupt Clear Register
  __I  uint32_t Timer1RIS;    // 0x10, Raw Interrupt Status Register
  __I  uint32_t Timer1MIS;    // 0x14, Masked Interrupt Status Register
  __IO uint32_t Timer1BGL;    // 0x18, Background Load Register
  __IO uint32_t RESERVED;     // 0x1C
  __IO uint32_t Timer2Load;   // 0x20, Load Register
  __I  uint32_t Timer2Value;  // 0x24, Current Value Register
  __IO uint32_t Timer2Ctrl;   // 0x28, Control Register
  __O  uint32_t Timer2IntClr; // 0x2C, Interrupt Clear Register
  __I  uint32_t Timer2RIS;    // 0x30, Raw Interrupt Status Register
  __I  uint32_t Timer2MIS;    // 0x34, Masked Interrupt Status Register
  __IO uint32_t Timer2BGL;    // 0x38, Background Load Register
} TIMER_TypeDef;

#define TIMER_CTRL_ONESHOT  (1 << 0)
#define TIMER_CTRL_SIZE     (1 << 1)
#define TIMER_CTRL_PRESCALE (3 << 2)
#define TIMER_CTRL_INT_EN   (1 << 5)
#define TIMER_CTRL_PERIODIC (1 << 6)
#define TIMER_CTRL_ENABLE   (1 << 7)

#define TIMER_CTRL_MODE_MASK (TIMER_CTRL_ONESHOT | TIMER_CTRL_PERIODIC)
#define TIMER_INTERRUPT_MASK (1 << 0)

typedef enum
{
  TIMER_SIZE_16 = 0,
  TIMER_SIZE_32 = TIMER_CTRL_SIZE,
} TIMER_SizeTypeDef;

typedef enum
{
  TIMER_MODE_FREE_RUNNING = 0,
  TIMER_MODE_PERIODIC     = TIMER_CTRL_PERIODIC,
  TIMER_MODE_ONE_SHOT     = TIMER_CTRL_ONESHOT,
} TIMER_ModeTypeDef;

typedef enum
{
  TIMER_PRESCALE_1   = 0b00 << 2,
  TIMER_PRESCALE_16  = 0b01 << 2,
  TIMER_PRESCALE_256 = 0b10 << 2,
} TIMER_PrescaleTypeDef;

static inline void TIM_SetMode1(TIMER_TypeDef *tim, TIMER_ModeTypeDef mode) { MODIFY_BIT(tim->Timer1Ctrl, TIMER_CTRL_MODE_MASK, mode); }
static inline void TIM_SetMode2(TIMER_TypeDef *tim, TIMER_ModeTypeDef mode) { MODIFY_BIT(tim->Timer2Ctrl, TIMER_CTRL_MODE_MASK, mode); }

static inline void TIM_SetSize1(TIMER_TypeDef *tim, TIMER_SizeTypeDef size) { MODIFY_BIT(tim->Timer1Ctrl, TIMER_CTRL_SIZE, size); }
static inline void TIM_SetSize2(TIMER_TypeDef *tim, TIMER_SizeTypeDef size) { MODIFY_BIT(tim->Timer2Ctrl, TIMER_CTRL_SIZE, size); }

static inline void TIM_SetPrescaler1(TIMER_TypeDef *tim, TIMER_PrescaleTypeDef psc) { MODIFY_BIT(tim->Timer1Ctrl, TIMER_CTRL_PRESCALE, psc); }
static inline void TIM_SetPrescaler2(TIMER_TypeDef *tim, TIMER_PrescaleTypeDef psc) { MODIFY_BIT(tim->Timer2Ctrl, TIMER_CTRL_PRESCALE, psc); }

static inline void TIM_EnableInt1(TIMER_TypeDef *tim)  { tim->Timer1Ctrl |=  TIMER_CTRL_INT_EN; }
static inline void TIM_EnableInt2(TIMER_TypeDef *tim)  { tim->Timer2Ctrl |=  TIMER_CTRL_INT_EN; }
static inline void TIM_DisableInt1(TIMER_TypeDef *tim) { tim->Timer1Ctrl &= ~TIMER_CTRL_INT_EN; }
static inline void TIM_DisableInt2(TIMER_TypeDef *tim) { tim->Timer2Ctrl &= ~TIMER_CTRL_INT_EN; }

static inline void TIM_ClearInt1(TIMER_TypeDef *tim) { tim->Timer1IntClr = TIMER_INTERRUPT_MASK; }
static inline void TIM_ClearInt2(TIMER_TypeDef *tim) { tim->Timer2IntClr = TIMER_INTERRUPT_MASK; }

// TIMER_INTERRUPT_MASK is not used since that's the only interrupt bit
static inline bool TIM_IsRawIntActive1   (TIMER_TypeDef *tim) { return tim->Timer1RIS; }
static inline bool TIM_IsRawIntActive2   (TIMER_TypeDef *tim) { return tim->Timer2RIS; }
static inline bool TIM_IsMaskedIntActive1(TIMER_TypeDef *tim) { return tim->Timer1MIS; }
static inline bool TIM_IsMaskedIntActive2(TIMER_TypeDef *tim) { return tim->Timer2MIS; }

static inline void TIM_SetLoad1(TIMER_TypeDef *tim, uint32_t load) { tim->Timer1Load = load; }
static inline void TIM_SetLoad2(TIMER_TypeDef *tim, uint32_t load) { tim->Timer2Load = load; }

static inline uint32_t TIM_GetLoad1(TIMER_TypeDef *tim)  { return tim->Timer1Load;  }
static inline uint32_t TIM_GetLoad2(TIMER_TypeDef *tim)  { return tim->Timer2Load;  }
static inline uint32_t TIM_GetValue1(TIMER_TypeDef *tim) { return tim->Timer1Value; }
static inline uint32_t TIM_GetValue2(TIMER_TypeDef *tim) { return tim->Timer2Value; }

static inline void TIM_SetBackGroundLoad1(TIMER_TypeDef *tim, uint32_t load) { tim->Timer1BGL = load; }
static inline void TIM_SetBackGroundLoad2(TIMER_TypeDef *tim, uint32_t load) { tim->Timer2BGL = load; }

static inline void TIM_EnableTimer1(TIMER_TypeDef *tim)  { tim->Timer1Ctrl |=  TIMER_CTRL_ENABLE; }
static inline void TIM_EnableTimer2(TIMER_TypeDef *tim)  { tim->Timer2Ctrl |=  TIMER_CTRL_ENABLE; }
static inline void TIM_DisableTimer1(TIMER_TypeDef *tim) { tim->Timer1Ctrl &= ~TIMER_CTRL_ENABLE; }
static inline void TIM_DisableTimer2(TIMER_TypeDef *tim) { tim->Timer2Ctrl &= ~TIMER_CTRL_ENABLE; }

void TIM_Init1(TIMER_TypeDef *tim, uint32_t timeInUs, TIMER_ModeTypeDef mode);
void TIM_Init2(TIMER_TypeDef *tim, uint32_t timeInUs, TIMER_ModeTypeDef mode);

#ifdef __cplusplus
}
#endif

#endif
