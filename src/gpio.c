#include "gpio.h"
#include "system.h"

void GPIO_IntConfig(GPIO_TypeDef *gpio, uint8_t bits, GPIO_IntModeTypeDef intmode)
{
  switch (intmode)
  {
  case GPIO_INTMODE_LOWLEVEL:
    gpio->GpioIS  |= bits;
    gpio->GpioIEV &= ~bits;
    break;
  case GPIO_INTMODE_HIGHLEVEL:
    gpio->GpioIS  |= bits;
    gpio->GpioIEV |= bits;
    break;
  case GPIO_INTMODE_FALLEDGE:
    gpio->GpioIS  &= ~bits;
    gpio->GpioIEV &= ~bits;
    gpio->GpioIBE &= ~bits;
    break;
  case GPIO_INTMODE_RISEEDGE:
    gpio->GpioIS  &= ~bits;
    gpio->GpioIEV |= bits;
    gpio->GpioIBE &= ~bits;
    break;
  case GPIO_INTMODE_BOTHEDGE:
    gpio->GpioIS  &= ~bits;
    gpio->GpioIBE |= bits;
    break;
  default:
    break;
  }
}
