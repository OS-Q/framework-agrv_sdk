#ifndef _AGM_GPIO_H
#define _AGM_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include "mac.h"

typedef struct
{
  __IO uint32_t GpioDATA[256]; // 0x00-0x3FC, Data register
  __IO uint32_t GpioDIR;       // 0x400, Data direction register
  __IO uint32_t GpioIS;        // 0x404, Interrupt sense register
  __IO uint32_t GpioIBE;       // 0x408, Interrupt both-edges register
  __IO uint32_t GpioIEV;       // 0x40C, Interrupt event register
  __IO uint32_t GpioIE;        // 0x410, Interrupt mask register
  __I  uint32_t GpioRIS;       // 0x414, Raw interrupt status register
  __I  uint32_t GpioMIS;       // 0x418, Masked interrupt status register
  __O  uint32_t GpioIC;        // 0x41C, Interrupt clear register
  __IO uint32_t GpioAFSEL;     // 0x420, Mode control select register
} GPIO_TypeDef;

#define GPIO_BIT0  (1 << 0)
#define GPIO_BIT1  (1 << 1)
#define GPIO_BIT2  (1 << 2)
#define GPIO_BIT3  (1 << 3)
#define GPIO_BIT4  (1 << 4)
#define GPIO_BIT5  (1 << 5)
#define GPIO_BIT6  (1 << 6)
#define GPIO_BIT7  (1 << 7)
#define GPIO_BIT_NONE 0x00
#define GPIO_BIT_ALL  0xff

typedef enum {
  GPIO_INTMODE_LOWLEVEL  = 0,
  GPIO_INTMODE_HIGHLEVEL = 1,
  GPIO_INTMODE_FALLEDGE  = 2,
  GPIO_INTMODE_RISEEDGE  = 3,
  GPIO_INTMODE_BOTHEDGE  = 4
} GPIO_IntModeTypeDef;

static inline void    GPIO_SetOutput(GPIO_TypeDef *gpio, uint8_t bits) { gpio->GpioDIR |=  bits; }
static inline void    GPIO_SetInput (GPIO_TypeDef *gpio, uint8_t bits) { gpio->GpioDIR &= ~bits; }
static inline void    GPIO_SetHigh  (GPIO_TypeDef *gpio, uint8_t bits) { gpio->GpioDATA[bits] = 0xff; }
static inline void    GPIO_SetLow   (GPIO_TypeDef *gpio, uint8_t bits) { gpio->GpioDATA[bits] = 0x00; }
static inline void    GPIO_SetValue (GPIO_TypeDef *gpio, uint8_t bits, uint8_t values) { gpio->GpioDATA[bits] = values; }
static inline uint8_t GPIO_GetValue (GPIO_TypeDef *gpio, uint8_t bits) { return gpio->GpioDATA[bits]; }
static inline void    GPIO_Toggle   (GPIO_TypeDef *gpio, uint8_t bits) { GPIO_SetValue(gpio, bits, ~GPIO_GetValue(gpio, bits)); }

static inline void GPIO_SetHardwareMode(GPIO_TypeDef *gpio, uint8_t bits) { gpio->GpioAFSEL |=  bits; }
static inline void GPIO_SetSoftwareMode(GPIO_TypeDef *gpio, uint8_t bits) { gpio->GpioAFSEL &= ~bits; }

static inline void GPIO_EnableInt (GPIO_TypeDef *gpio, uint8_t bits) { gpio->GpioIE |=  bits; }
static inline void GPIO_DisableInt(GPIO_TypeDef *gpio, uint8_t bits) { gpio->GpioIE &= ~bits; }
static inline void GPIO_ClearInt  (GPIO_TypeDef *gpio, uint8_t bits) { gpio->GpioIC  =  bits; }

// Can check multiple interrupts in one call. Will return true if any bit is active
static inline bool GPIO_IsRawIntActive   (GPIO_TypeDef *gpio, uint8_t bits) { return gpio->GpioRIS & bits; }
static inline bool GPIO_IsMaskedIntActive(GPIO_TypeDef *gpio, uint8_t bits) { return gpio->GpioMIS & bits; }

void GPIO_IntConfig(GPIO_TypeDef *gpio, uint8_t bits, GPIO_IntModeTypeDef intmode);

// Use double expansion to allow macro in the parameters
#define GPIO_AF_PIN_(__PER, __ID, __PIN) __PER##__ID##_##__PIN
#define GPIO_AF_PIN(__PER, __ID, __PIN) GPIO_AF_PIN_(__PER, __ID, __PIN)

#define GPIO_AF_ENABLE_(__PIN) { \
  XLEN_TYPE clken = SYS->APB_CLKENABLE; \
  SYS->APB_CLKENABLE = clken | APB_MASK_GPIOx(__PIN##_AF_GPIO); \
  GPIOx(__PIN##_AF_GPIO)->GpioAFSEL |= __PIN##_AF_GPIO_MASK; \
  SYS->APB_CLKENABLE = clken; \
}
#define GPIO_AF_ENABLE(__PIN) GPIO_AF_ENABLE_(__PIN)

#define GPIO_AF_DISABLE_(__PIN) { \
  XLEN_TYPE clken = SYS->APB_CLKENABLE; \
  SYS->APB_CLKENABLE = clken | APB_MASK_GPIOx(__PIN##_AF_GPIO); \
  GPIOx(__PIN##_AF_GPIO)->GpioAFSEL &= ~__PIN##_AF_GPIO_MASK; \
  SYS->APB_CLKENABLE = clken; \
}
#define GPIO_AF_DISABLE(__PIN) GPIO_AF_DISABLE_(__PIN)

#ifdef __cplusplus
}
#endif

#endif
