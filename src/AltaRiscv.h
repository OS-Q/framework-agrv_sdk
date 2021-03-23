#ifndef ALTA_RISCV_H
#define ALTA_RISCV_H

#define FLASH_IRQn 1
#define RTC_IRQn 2
#define FLASH_DMA_REQ 0
#define EXT_DMA0_REQ 1
#define EXT_DMA1_REQ 2
#define EXT_DMA2_REQ 3
#define EXT_DMA3_REQ 4
#define EXT_DMAx_REQ(i) (i == 0 ? EXT_DMA0_REQ : i == 1 ? EXT_DMA1_REQ : i == 2 ? EXT_DMA2_REQ : EXT_DMA3_REQ)

#define FCB0_BASE 0x40010000
#define FCB0 ((FCB_TypeDef *) FCB0_BASE)
#define APB_MASK_FCB0 (1 << 0)
#define FCB0_DMA_REQ 5
#define FCB0_IRQn 3

#define WATCHDOG0_BASE 0x40011000
#define WATCHDOG0 ((WATCHDOG_TypeDef *) WATCHDOG0_BASE)
#define APB_MASK_WATCHDOG0 (1 << 1)
#define WATCHDOG0_IRQn 4

#define SPI0_BASE 0x40012000
#define SPI0 ((SPI_TypeDef *) SPI0_BASE)
#define APB_MASK_SPI0 (1 << 2)
#define SPI0_TX_DMA_REQ 6
#define SPI0_RX_DMA_REQ 7
#define SPI0_IRQn 5

#define SPI1_BASE 0x40013000
#define SPI1 ((SPI_TypeDef *) SPI1_BASE)
#define APB_MASK_SPI1 (1 << 3)
#define SPI1_TX_DMA_REQ 8
#define SPI1_RX_DMA_REQ 9
#define SPI1_IRQn 6

#define GPIO0_BASE 0x40014000
#define GPIO0 ((GPIO_TypeDef *) GPIO0_BASE)
#define APB_MASK_GPIO0 (1 << 4)
#define GPIO0_IRQn 7

#define GPIO1_BASE 0x40015000
#define GPIO1 ((GPIO_TypeDef *) GPIO1_BASE)
#define APB_MASK_GPIO1 (1 << 5)
#define GPIO1_IRQn 8

#define GPIO2_BASE 0x40016000
#define GPIO2 ((GPIO_TypeDef *) GPIO2_BASE)
#define APB_MASK_GPIO2 (1 << 6)
#define GPIO2_IRQn 9

#define GPIO3_BASE 0x40017000
#define GPIO3 ((GPIO_TypeDef *) GPIO3_BASE)
#define APB_MASK_GPIO3 (1 << 7)
#define GPIO3_IRQn 10

#define GPIO4_BASE 0x40018000
#define GPIO4 ((GPIO_TypeDef *) GPIO4_BASE)
#define APB_MASK_GPIO4 (1 << 8)
#define GPIO4_IRQn 11

#define GPIO5_BASE 0x40019000
#define GPIO5 ((GPIO_TypeDef *) GPIO5_BASE)
#define APB_MASK_GPIO5 (1 << 9)
#define GPIO5_IRQn 12

#define GPIO6_BASE 0x4001A000
#define GPIO6 ((GPIO_TypeDef *) GPIO6_BASE)
#define APB_MASK_GPIO6 (1 << 10)
#define GPIO6_IRQn 13

#define GPIO7_BASE 0x4001B000
#define GPIO7 ((GPIO_TypeDef *) GPIO7_BASE)
#define APB_MASK_GPIO7 (1 << 11)
#define GPIO7_IRQn 14

#define GPIO8_BASE 0x4001C000
#define GPIO8 ((GPIO_TypeDef *) GPIO8_BASE)
#define APB_MASK_GPIO8 (1 << 12)
#define GPIO8_IRQn 15

#define GPIO9_BASE 0x4001D000
#define GPIO9 ((GPIO_TypeDef *) GPIO9_BASE)
#define APB_MASK_GPIO9 (1 << 13)
#define GPIO9_IRQn 16

#define TIMER0_BASE 0x4001E000
#define TIMER0 ((TIMER_TypeDef *) TIMER0_BASE)
#define APB_MASK_TIMER0 (1 << 14)
#define TIMER0_IRQn 17

#define TIMER1_BASE 0x4001F000
#define TIMER1 ((TIMER_TypeDef *) TIMER1_BASE)
#define APB_MASK_TIMER1 (1 << 15)
#define TIMER1_IRQn 18

#define GPTIMER0_BASE 0x40020000
#define GPTIMER0 ((GPTIMER_TypeDef *) GPTIMER0_BASE)
#define APB_MASK_GPTIMER0 (1 << 16)
#define GPTIMER0_UPDATE_DMA_REQ 10
#define GPTIMER0_CC_DMA0_REQ 11
#define GPTIMER0_CC_DMA1_REQ 12
#define GPTIMER0_CC_DMA2_REQ 13
#define GPTIMER0_CC_DMA3_REQ 14
#define GPTIMER0_COM_DMA_REQ 15
#define GPTIMER0_TRIGGER_DMA_REQ 0
#define GPTIMER0_IRQn 19

#define GPTIMER1_BASE 0x40021000
#define GPTIMER1 ((GPTIMER_TypeDef *) GPTIMER1_BASE)
#define APB_MASK_GPTIMER1 (1 << 17)
#define GPTIMER1_UPDATE_DMA_REQ 1
#define GPTIMER1_CC_DMA0_REQ 2
#define GPTIMER1_CC_DMA1_REQ 3
#define GPTIMER1_CC_DMA2_REQ 4
#define GPTIMER1_CC_DMA3_REQ 5
#define GPTIMER1_COM_DMA_REQ 6
#define GPTIMER1_TRIGGER_DMA_REQ 7
#define GPTIMER1_IRQn 20

#define GPTIMER2_BASE 0x40022000
#define GPTIMER2 ((GPTIMER_TypeDef *) GPTIMER2_BASE)
#define APB_MASK_GPTIMER2 (1 << 18)
#define GPTIMER2_UPDATE_DMA_REQ 8
#define GPTIMER2_CC_DMA0_REQ 9
#define GPTIMER2_CC_DMA1_REQ 10
#define GPTIMER2_CC_DMA2_REQ 11
#define GPTIMER2_CC_DMA3_REQ 12
#define GPTIMER2_COM_DMA_REQ 13
#define GPTIMER2_TRIGGER_DMA_REQ 14
#define GPTIMER2_IRQn 21

#define GPTIMER3_BASE 0x40023000
#define GPTIMER3 ((GPTIMER_TypeDef *) GPTIMER3_BASE)
#define APB_MASK_GPTIMER3 (1 << 19)
#define GPTIMER3_UPDATE_DMA_REQ 15
#define GPTIMER3_CC_DMA0_REQ 0
#define GPTIMER3_CC_DMA1_REQ 1
#define GPTIMER3_CC_DMA2_REQ 2
#define GPTIMER3_CC_DMA3_REQ 3
#define GPTIMER3_COM_DMA_REQ 4
#define GPTIMER3_TRIGGER_DMA_REQ 5
#define GPTIMER3_IRQn 22

#define GPTIMER4_BASE 0x40024000
#define GPTIMER4 ((GPTIMER_TypeDef *) GPTIMER4_BASE)
#define APB_MASK_GPTIMER4 (1 << 20)
#define GPTIMER4_UPDATE_DMA_REQ 6
#define GPTIMER4_CC_DMA0_REQ 7
#define GPTIMER4_CC_DMA1_REQ 8
#define GPTIMER4_CC_DMA2_REQ 9
#define GPTIMER4_CC_DMA3_REQ 10
#define GPTIMER4_COM_DMA_REQ 11
#define GPTIMER4_TRIGGER_DMA_REQ 12
#define GPTIMER4_IRQn 23

#define UART0_BASE 0x40025000
#define UART0 ((UART_TypeDef *) UART0_BASE)
#define APB_MASK_UART0 (1 << 21)
#define UART0_TX_DMA_REQ 13
#define UART0_RX_DMA_REQ 14
#define UART0_IRQn 24

#define UART1_BASE 0x40026000
#define UART1 ((UART_TypeDef *) UART1_BASE)
#define APB_MASK_UART1 (1 << 22)
#define UART1_TX_DMA_REQ 15
#define UART1_RX_DMA_REQ 0
#define UART1_IRQn 25

#define UART2_BASE 0x40027000
#define UART2 ((UART_TypeDef *) UART2_BASE)
#define APB_MASK_UART2 (1 << 23)
#define UART2_TX_DMA_REQ 1
#define UART2_RX_DMA_REQ 2
#define UART2_IRQn 26

#define UART3_BASE 0x40028000
#define UART3 ((UART_TypeDef *) UART3_BASE)
#define APB_MASK_UART3 (1 << 24)
#define UART3_TX_DMA_REQ 3
#define UART3_RX_DMA_REQ 4
#define UART3_IRQn 27

#define UART4_BASE 0x40029000
#define UART4 ((UART_TypeDef *) UART4_BASE)
#define APB_MASK_UART4 (1 << 25)
#define UART4_TX_DMA_REQ 5
#define UART4_RX_DMA_REQ 6
#define UART4_IRQn 28

#define CAN0_BASE 0x4002A000
#define CAN0 ((CAN_TypeDef *) CAN0_BASE)
#define APB_MASK_CAN0 (1 << 26)
#define CAN0_IRQn 29

#define I2C0_BASE 0x4002B000
#define I2C0 ((I2C_TypeDef *) I2C0_BASE)
#define APB_MASK_I2C0 (1 << 27)
#define I2C0_IRQn 30

#define I2C1_BASE 0x4002C000
#define I2C1 ((I2C_TypeDef *) I2C1_BASE)
#define APB_MASK_I2C1 (1 << 28)
#define I2C1_IRQn 31

#define DMAC0_BASE 0x41000000
#define DMAC0 ((DMAC_TypeDef *) DMAC0_BASE)
#define AHB_MASK_DMAC0 (1 << 0)
#define DMAC0_INTR_IRQn 32
#define DMAC0_INTTC_IRQn 33
#define DMAC0_INTERR_IRQn 34

#define USB0_BASE 0x41001000
#define USB0 ((USB_TypeDef *) USB0_BASE)
#define AHB_MASK_USB0 (1 << 1)
#define USB0_IRQn 35

#define CRC0_BASE 0x41002000
#define CRC0 ((CRC_TypeDef *) CRC0_BASE)
#define AHB_MASK_CRC0 (1 << 2)

#define MAC0_BASE 0x41040000
#define MAC0 ((MAC_TypeDef *) MAC0_BASE)
#define AHB_MASK_MAC0 (1 << 3)
#define MAC0_IRQn 36

#define FCB_COUNT 1
#define FCBx(i) (FCB0)
#define APB_MASK_FCBx(i) (APB_MASK_FCB0)
#define FCBx_IRQn(i) (FCB0_IRQn)
#define FCBx_DMA_REQ(i) (FCB0_DMA_REQ)

#define WATCHDOG_COUNT 1
#define WATCHDOGx(i) (WATCHDOG0)
#define APB_MASK_WATCHDOGx(i) (APB_MASK_WATCHDOG0)
#define WATCHDOGx_IRQn(i) (WATCHDOG0_IRQn)

#define SPI_COUNT 2
#define SPIx(i) (i == 0 ? SPI0 : SPI1)
#define APB_MASK_SPIx(i) (i == 0 ? APB_MASK_SPI0 : APB_MASK_SPI1)
#define SPIx_IRQn(i) (i == 0 ? SPI0_IRQn : SPI1_IRQn)
#define SPIx_TX_DMA_REQ(i) (i == 0 ? SPI0_TX_DMA_REQ : SPI1_TX_DMA_REQ)
#define SPIx_RX_DMA_REQ(i) (i == 0 ? SPI0_RX_DMA_REQ : SPI1_RX_DMA_REQ)

#define GPIO_COUNT 10
#define GPIOx(i) (i == 0 ? GPIO0 : i == 1 ? GPIO1 : i == 2 ? GPIO2 : i == 3 ? GPIO3 : i == 4 ? GPIO4 : i == 5 ? GPIO5 : i == 6 ? GPIO6 : i == 7 ? GPIO7 : i == 8 ? GPIO8 : GPIO9)
#define APB_MASK_GPIOx(i) (i == 0 ? APB_MASK_GPIO0 : i == 1 ? APB_MASK_GPIO1 : i == 2 ? APB_MASK_GPIO2 : i == 3 ? APB_MASK_GPIO3 : i == 4 ? APB_MASK_GPIO4 : i == 5 ? APB_MASK_GPIO5 : i == 6 ? APB_MASK_GPIO6 : i == 7 ? APB_MASK_GPIO7 : i == 8 ? APB_MASK_GPIO8 : APB_MASK_GPIO9)
#define GPIOx_IRQn(i) (i == 0 ? GPIO0_IRQn : i == 1 ? GPIO1_IRQn : i == 2 ? GPIO2_IRQn : i == 3 ? GPIO3_IRQn : i == 4 ? GPIO4_IRQn : i == 5 ? GPIO5_IRQn : i == 6 ? GPIO6_IRQn : i == 7 ? GPIO7_IRQn : i == 8 ? GPIO8_IRQn : GPIO9_IRQn)

#define TIMER_COUNT 2
#define TIMERx(i) (i == 0 ? TIMER0 : TIMER1)
#define APB_MASK_TIMERx(i) (i == 0 ? APB_MASK_TIMER0 : APB_MASK_TIMER1)
#define TIMERx_IRQn(i) (i == 0 ? TIMER0_IRQn : TIMER1_IRQn)

#define GPTIMER_COUNT 5
#define GPTIMERx(i) (i == 0 ? GPTIMER0 : i == 1 ? GPTIMER1 : i == 2 ? GPTIMER2 : i == 3 ? GPTIMER3 : GPTIMER4)
#define APB_MASK_GPTIMERx(i) (i == 0 ? APB_MASK_GPTIMER0 : i == 1 ? APB_MASK_GPTIMER1 : i == 2 ? APB_MASK_GPTIMER2 : i == 3 ? APB_MASK_GPTIMER3 : APB_MASK_GPTIMER4)
#define GPTIMERx_IRQn(i) (i == 0 ? GPTIMER0_IRQn : i == 1 ? GPTIMER1_IRQn : i == 2 ? GPTIMER2_IRQn : i == 3 ? GPTIMER3_IRQn : GPTIMER4_IRQn)
#define GPTIMERx_UPDATE_DMA_REQ(i) (i == 0 ? GPTIMER0_UPDATE_DMA_REQ : i == 1 ? GPTIMER1_UPDATE_DMA_REQ : i == 2 ? GPTIMER2_UPDATE_DMA_REQ : i == 3 ? GPTIMER3_UPDATE_DMA_REQ : GPTIMER4_UPDATE_DMA_REQ)
#define GPTIMERx_CC_DMA0_REQ(i) (i == 0 ? GPTIMER0_CC_DMA0_REQ : i == 1 ? GPTIMER1_CC_DMA0_REQ : i == 2 ? GPTIMER2_CC_DMA0_REQ : i == 3 ? GPTIMER3_CC_DMA0_REQ : GPTIMER4_CC_DMA0_REQ)
#define GPTIMERx_CC_DMA1_REQ(i) (i == 0 ? GPTIMER0_CC_DMA1_REQ : i == 1 ? GPTIMER1_CC_DMA1_REQ : i == 2 ? GPTIMER2_CC_DMA1_REQ : i == 3 ? GPTIMER3_CC_DMA1_REQ : GPTIMER4_CC_DMA1_REQ)
#define GPTIMERx_CC_DMA2_REQ(i) (i == 0 ? GPTIMER0_CC_DMA2_REQ : i == 1 ? GPTIMER1_CC_DMA2_REQ : i == 2 ? GPTIMER2_CC_DMA2_REQ : i == 3 ? GPTIMER3_CC_DMA2_REQ : GPTIMER4_CC_DMA2_REQ)
#define GPTIMERx_CC_DMA3_REQ(i) (i == 0 ? GPTIMER0_CC_DMA3_REQ : i == 1 ? GPTIMER1_CC_DMA3_REQ : i == 2 ? GPTIMER2_CC_DMA3_REQ : i == 3 ? GPTIMER3_CC_DMA3_REQ : GPTIMER4_CC_DMA3_REQ)
#define GPTIMERx_COM_DMA_REQ(i) (i == 0 ? GPTIMER0_COM_DMA_REQ : i == 1 ? GPTIMER1_COM_DMA_REQ : i == 2 ? GPTIMER2_COM_DMA_REQ : i == 3 ? GPTIMER3_COM_DMA_REQ : GPTIMER4_COM_DMA_REQ)
#define GPTIMERx_TRIGGER_DMA_REQ(i) (i == 0 ? GPTIMER0_TRIGGER_DMA_REQ : i == 1 ? GPTIMER1_TRIGGER_DMA_REQ : i == 2 ? GPTIMER2_TRIGGER_DMA_REQ : i == 3 ? GPTIMER3_TRIGGER_DMA_REQ : GPTIMER4_TRIGGER_DMA_REQ)

#define UART_COUNT 5
#define UARTx(i) (i == 0 ? UART0 : i == 1 ? UART1 : i == 2 ? UART2 : i == 3 ? UART3 : UART4)
#define APB_MASK_UARTx(i) (i == 0 ? APB_MASK_UART0 : i == 1 ? APB_MASK_UART1 : i == 2 ? APB_MASK_UART2 : i == 3 ? APB_MASK_UART3 : APB_MASK_UART4)
#define UARTx_IRQn(i) (i == 0 ? UART0_IRQn : i == 1 ? UART1_IRQn : i == 2 ? UART2_IRQn : i == 3 ? UART3_IRQn : UART4_IRQn)
#define UARTx_TX_DMA_REQ(i) (i == 0 ? UART0_TX_DMA_REQ : i == 1 ? UART1_TX_DMA_REQ : i == 2 ? UART2_TX_DMA_REQ : i == 3 ? UART3_TX_DMA_REQ : UART4_TX_DMA_REQ)
#define UARTx_RX_DMA_REQ(i) (i == 0 ? UART0_RX_DMA_REQ : i == 1 ? UART1_RX_DMA_REQ : i == 2 ? UART2_RX_DMA_REQ : i == 3 ? UART3_RX_DMA_REQ : UART4_RX_DMA_REQ)

#define CAN_COUNT 1
#define CANx(i) (CAN0)
#define APB_MASK_CANx(i) (APB_MASK_CAN0)
#define CANx_IRQn(i) (CAN0_IRQn)

#define I2C_COUNT 2
#define I2Cx(i) (i == 0 ? I2C0 : I2C1)
#define APB_MASK_I2Cx(i) (i == 0 ? APB_MASK_I2C0 : APB_MASK_I2C1)
#define I2Cx_IRQn(i) (i == 0 ? I2C0_IRQn : I2C1_IRQn)

#define DMAC_COUNT 1
#define DMACx(i) (DMAC0)
#define AHB_MASK_DMACx(i) (AHB_MASK_DMAC0)
#define DMACx_INTR_IRQn(i) (DMAC0_INTR_IRQn)
#define DMACx_INTTC_IRQn(i) (DMAC0_INTTC_IRQn)
#define DMACx_INTERR_IRQn(i) (DMAC0_INTERR_IRQn)

#define USB_COUNT 1
#define USBx(i) (USB0)
#define AHB_MASK_USBx(i) (AHB_MASK_USB0)
#define USBx_IRQn(i) (USB0_IRQn)

#define CRC_COUNT 1
#define CRCx(i) (CRC0)
#define AHB_MASK_CRCx(i) (AHB_MASK_CRC0)

#define MAC_COUNT 1
#define MACx(i) (MAC0)
#define AHB_MASK_MACx(i) (AHB_MASK_MAC0)
#define MACx_IRQn(i) (MAC0_IRQn)

// PLIC external interrupts
#define EXT_INT0_IRQn 37
#define EXT_INT1_IRQn 38
#define EXT_INT2_IRQn 39
#define EXT_INT3_IRQn 40
#define EXT_INT4_IRQn 41
#define EXT_INT5_IRQn 42
#define EXT_INT6_IRQn 43
#define EXT_INT7_IRQn 44
#define EXT_INTx_IRQn(i) (i == 0 ? EXT_INT0_IRQn : i == 1 ? EXT_INT1_IRQn : i == 2 ? EXT_INT2_IRQn : i == 3 ? EXT_INT3_IRQn : i == 4 ? EXT_INT4_IRQn : i == 5 ? EXT_INT5_IRQn : i == 6 ? EXT_INT6_IRQn : EXT_INT7_IRQn)

#define PLIC_INTERNAL_INTERRUPT_COUNT 36
#define PLIC_EXTERNAL_INTERRUPT_COUNT 8
#define PLIC_TOTAL_INTERRUPT_COUNT 44
#define PLIC_MAX_PRIORITY 15

// CLINT local interrupts
#define LOCAL_INT_COUNT 4
#define LOCAL_INT0_IRQn 16
#define LOCAL_INT1_IRQn 17
#define LOCAL_INT2_IRQn 18
#define LOCAL_INT3_IRQn 19
#define LOCAL_INTx_IRQn(i) (i == 0 ? LOCAL_INT0_IRQn : i == 1 ? LOCAL_INT1_IRQn : i == 2 ? LOCAL_INT2_IRQn : LOCAL_INT3_IRQn)

// Helper macro to declare all the isr functions with optional attributes. Do not declare them with a weak 
// attribute here, since that may yield multiple weak function definitions which can cause undefined behavior.
#define INT_DECLAR_ISR_FUNCTIONS(__attr) \
  void FLASH_isr(void) __attr; \
  void RTC_isr(void) __attr; \
  void FCB0_isr(void) __attr; \
  void WATCHDOG0_isr(void) __attr; \
  void SPI0_isr(void) __attr; \
  void SPI1_isr(void) __attr; \
  void GPIO0_isr(void) __attr; \
  void GPIO1_isr(void) __attr; \
  void GPIO2_isr(void) __attr; \
  void GPIO3_isr(void) __attr; \
  void GPIO4_isr(void) __attr; \
  void GPIO5_isr(void) __attr; \
  void GPIO6_isr(void) __attr; \
  void GPIO7_isr(void) __attr; \
  void GPIO8_isr(void) __attr; \
  void GPIO9_isr(void) __attr; \
  void TIMER0_isr(void) __attr; \
  void TIMER1_isr(void) __attr; \
  void GPTIMER0_isr(void) __attr; \
  void GPTIMER1_isr(void) __attr; \
  void GPTIMER2_isr(void) __attr; \
  void GPTIMER3_isr(void) __attr; \
  void GPTIMER4_isr(void) __attr; \
  void UART0_isr(void) __attr; \
  void UART1_isr(void) __attr; \
  void UART2_isr(void) __attr; \
  void UART3_isr(void) __attr; \
  void UART4_isr(void) __attr; \
  void CAN0_isr(void) __attr; \
  void I2C0_isr(void) __attr; \
  void I2C1_isr(void) __attr; \
  void DMAC0_INTR_isr(void) __attr; \
  void DMAC0_INTTC_isr(void) __attr; \
  void DMAC0_INTERR_isr(void) __attr; \
  void USB0_isr(void) __attr; \
  void MAC0_isr(void) __attr; \
  void EXT_INT0_isr(void) __attr; \
  void EXT_INT1_isr(void) __attr; \
  void EXT_INT2_isr(void) __attr; \
  void EXT_INT3_isr(void) __attr; \
  void EXT_INT4_isr(void) __attr; \
  void EXT_INT5_isr(void) __attr; \
  void EXT_INT6_isr(void) __attr; \
  void EXT_INT7_isr(void) __attr; \
  void MSOFTWARE_isr(void) __attr; \
  void MTIMER_isr(void) __attr; \
  void LOCAL_INT0_isr(void) __attr; \
  void LOCAL_INT1_isr(void) __attr; \
  void LOCAL_INT2_isr(void) __attr; \
  void LOCAL_INT3_isr(void) __attr; \

// These helper macros can be used to declare the isr vector tables. If not all IRQs are used these tables can be
// declared with a smaller size (largest used IRQn + 1) to save memory.
#define INT_DECLARE_PLIC_ISR(__SIZE) void (**plic_isr)(void)  = (void (*[__SIZE])(void))
#define INT_DECLARE_PLIC_ISR_TABLE INT_DECLARE_PLIC_ISR(45) { \
  NULL, \
  FLASH_isr, \
  RTC_isr, \
  FCB0_isr, \
  WATCHDOG0_isr, \
  SPI0_isr, \
  SPI1_isr, \
  GPIO0_isr, \
  GPIO1_isr, \
  GPIO2_isr, \
  GPIO3_isr, \
  GPIO4_isr, \
  GPIO5_isr, \
  GPIO6_isr, \
  GPIO7_isr, \
  GPIO8_isr, \
  GPIO9_isr, \
  TIMER0_isr, \
  TIMER1_isr, \
  GPTIMER0_isr, \
  GPTIMER1_isr, \
  GPTIMER2_isr, \
  GPTIMER3_isr, \
  GPTIMER4_isr, \
  UART0_isr, \
  UART1_isr, \
  UART2_isr, \
  UART3_isr, \
  UART4_isr, \
  CAN0_isr, \
  I2C0_isr, \
  I2C1_isr, \
  DMAC0_INTR_isr, \
  DMAC0_INTTC_isr, \
  DMAC0_INTERR_isr, \
  USB0_isr, \
  MAC0_isr, \
  EXT_INT0_isr, \
  EXT_INT1_isr, \
  EXT_INT2_isr, \
  EXT_INT3_isr, \
  EXT_INT4_isr, \
  EXT_INT5_isr, \
  EXT_INT6_isr, \
  EXT_INT7_isr, \
}
#define INT_DECLARE_CLINT_ISR(__SIZE) void (**clint_isr)(void)  = (void (*[__SIZE])(void))
#define INT_DECLARE_CLINT_ISR_TABLE INT_DECLARE_CLINT_ISR(20) { \
  NULL, \
  NULL, \
  NULL, \
  MSOFTWARE_isr, \
  NULL, \
  NULL, \
  NULL, \
  MTIMER_isr, \
  NULL, \
  NULL, \
  NULL, \
  NULL, \
  NULL, \
  NULL, \
  NULL, \
  NULL, \
  LOCAL_INT0_isr, \
  LOCAL_INT1_isr, \
  LOCAL_INT2_isr, \
  LOCAL_INT3_isr, \
}

// Wake up IDs
#define SYS_WAKEUP_EXT_INT0_ID 0
#define SYS_WAKEUP_EXT_INT1_ID 1
#define SYS_WAKEUP_EXT_INT2_ID 2
#define SYS_WAKEUP_EXT_INT3_ID 3
#define SYS_WAKEUP_EXT_INT4_ID 4
#define SYS_WAKEUP_EXT_INT5_ID 5
#define SYS_WAKEUP_EXT_INT6_ID 6
#define SYS_WAKEUP_EXT_INT7_ID 7
#define SYS_WAKEUP_ALARM_ID 8

// GPTIMER internal triggers
#define GPTIMER0_ITR0 GPTIMER1
#define GPTIMER0_ITR1 GPTIMER2
#define GPTIMER0_ITR2 GPTIMER3
#define GPTIMER0_ITR3 GPTIMER4

#define GPTIMER1_ITR0 GPTIMER2
#define GPTIMER1_ITR1 GPTIMER3
#define GPTIMER1_ITR2 GPTIMER4
#define GPTIMER1_ITR3 GPTIMER0

#define GPTIMER2_ITR0 GPTIMER3
#define GPTIMER2_ITR1 GPTIMER4
#define GPTIMER2_ITR2 GPTIMER0
#define GPTIMER2_ITR3 GPTIMER1

#define GPTIMER3_ITR0 GPTIMER4
#define GPTIMER3_ITR1 GPTIMER0
#define GPTIMER3_ITR2 GPTIMER1
#define GPTIMER3_ITR3 GPTIMER2

#define GPTIMER4_ITR0 GPTIMER0
#define GPTIMER4_ITR1 GPTIMER1
#define GPTIMER4_ITR2 GPTIMER2
#define GPTIMER4_ITR3 GPTIMER3

// GPIO alternative function pins
#define SPI0_SI_IO0_AF_GPIO 0
#define SPI0_SI_IO0_AF_GPIO_MASK (0x1 << 0)
#define SPI0_SI_IO0_AF_GPIO_INOUT

#define SPI0_SO_IO1_AF_GPIO 0
#define SPI0_SO_IO1_AF_GPIO_MASK (0x1 << 1)
#define SPI0_SO_IO1_AF_GPIO_INOUT

#define SPI0_WPN_IO2_AF_GPIO 0
#define SPI0_WPN_IO2_AF_GPIO_MASK (0x1 << 2)
#define SPI0_WPN_IO2_AF_GPIO_INOUT

#define SPI0_HOLDN_IO3_AF_GPIO 0
#define SPI0_HOLDN_IO3_AF_GPIO_MASK (0x1 << 3)
#define SPI0_HOLDN_IO3_AF_GPIO_INOUT

#define SPI1_SI_IO0_AF_GPIO 0
#define SPI1_SI_IO0_AF_GPIO_MASK (0x1 << 4)
#define SPI1_SI_IO0_AF_GPIO_INOUT

#define SPI1_SO_IO1_AF_GPIO 0
#define SPI1_SO_IO1_AF_GPIO_MASK (0x1 << 5)
#define SPI1_SO_IO1_AF_GPIO_INOUT

#define SPI1_WPN_IO2_AF_GPIO 0
#define SPI1_WPN_IO2_AF_GPIO_MASK (0x1 << 6)
#define SPI1_WPN_IO2_AF_GPIO_INOUT

#define SPI1_HOLDN_IO3_AF_GPIO 0
#define SPI1_HOLDN_IO3_AF_GPIO_MASK (0x1 << 7)
#define SPI1_HOLDN_IO3_AF_GPIO_INOUT

#define GPTIMER0_CH0_AF_GPIO 1
#define GPTIMER0_CH0_AF_GPIO_MASK (0x1 << 0)
#define GPTIMER0_CH0_AF_GPIO_INOUT

#define GPTIMER0_CH1_AF_GPIO 1
#define GPTIMER0_CH1_AF_GPIO_MASK (0x1 << 1)
#define GPTIMER0_CH1_AF_GPIO_INOUT

#define GPTIMER0_CH2_AF_GPIO 1
#define GPTIMER0_CH2_AF_GPIO_MASK (0x1 << 2)
#define GPTIMER0_CH2_AF_GPIO_INOUT

#define GPTIMER0_CH3_AF_GPIO 1
#define GPTIMER0_CH3_AF_GPIO_MASK (0x1 << 3)
#define GPTIMER0_CH3_AF_GPIO_INOUT

#define GPTIMER1_CH0_AF_GPIO 1
#define GPTIMER1_CH0_AF_GPIO_MASK (0x1 << 4)
#define GPTIMER1_CH0_AF_GPIO_INOUT

#define GPTIMER1_CH1_AF_GPIO 1
#define GPTIMER1_CH1_AF_GPIO_MASK (0x1 << 5)
#define GPTIMER1_CH1_AF_GPIO_INOUT

#define GPTIMER1_CH2_AF_GPIO 1
#define GPTIMER1_CH2_AF_GPIO_MASK (0x1 << 6)
#define GPTIMER1_CH2_AF_GPIO_INOUT

#define GPTIMER1_CH3_AF_GPIO 1
#define GPTIMER1_CH3_AF_GPIO_MASK (0x1 << 7)
#define GPTIMER1_CH3_AF_GPIO_INOUT

#define GPTIMER2_CH0_AF_GPIO 2
#define GPTIMER2_CH0_AF_GPIO_MASK (0x1 << 0)
#define GPTIMER2_CH0_AF_GPIO_INOUT

#define GPTIMER2_CH1_AF_GPIO 2
#define GPTIMER2_CH1_AF_GPIO_MASK (0x1 << 1)
#define GPTIMER2_CH1_AF_GPIO_INOUT

#define GPTIMER2_CH2_AF_GPIO 2
#define GPTIMER2_CH2_AF_GPIO_MASK (0x1 << 2)
#define GPTIMER2_CH2_AF_GPIO_INOUT

#define GPTIMER2_CH3_AF_GPIO 2
#define GPTIMER2_CH3_AF_GPIO_MASK (0x1 << 3)
#define GPTIMER2_CH3_AF_GPIO_INOUT

#define GPTIMER3_CH0_AF_GPIO 2
#define GPTIMER3_CH0_AF_GPIO_MASK (0x1 << 4)
#define GPTIMER3_CH0_AF_GPIO_INOUT

#define GPTIMER3_CH1_AF_GPIO 2
#define GPTIMER3_CH1_AF_GPIO_MASK (0x1 << 5)
#define GPTIMER3_CH1_AF_GPIO_INOUT

#define GPTIMER3_CH2_AF_GPIO 2
#define GPTIMER3_CH2_AF_GPIO_MASK (0x1 << 6)
#define GPTIMER3_CH2_AF_GPIO_INOUT

#define GPTIMER3_CH3_AF_GPIO 2
#define GPTIMER3_CH3_AF_GPIO_MASK (0x1 << 7)
#define GPTIMER3_CH3_AF_GPIO_INOUT

#define GPTIMER4_CH0_AF_GPIO 3
#define GPTIMER4_CH0_AF_GPIO_MASK (0x1 << 0)
#define GPTIMER4_CH0_AF_GPIO_INOUT

#define GPTIMER4_CH1_AF_GPIO 3
#define GPTIMER4_CH1_AF_GPIO_MASK (0x1 << 1)
#define GPTIMER4_CH1_AF_GPIO_INOUT

#define GPTIMER4_CH2_AF_GPIO 3
#define GPTIMER4_CH2_AF_GPIO_MASK (0x1 << 2)
#define GPTIMER4_CH2_AF_GPIO_INOUT

#define GPTIMER4_CH3_AF_GPIO 3
#define GPTIMER4_CH3_AF_GPIO_MASK (0x1 << 3)
#define GPTIMER4_CH3_AF_GPIO_INOUT

#define I2C0_SCL_AF_GPIO 3
#define I2C0_SCL_AF_GPIO_MASK (0x1 << 4)
#define I2C0_SCL_AF_GPIO_INOUT

#define I2C0_SDA_AF_GPIO 3
#define I2C0_SDA_AF_GPIO_MASK (0x1 << 5)
#define I2C0_SDA_AF_GPIO_INOUT

#define I2C1_SCL_AF_GPIO 3
#define I2C1_SCL_AF_GPIO_MASK (0x1 << 6)
#define I2C1_SCL_AF_GPIO_INOUT

#define I2C1_SDA_AF_GPIO 3
#define I2C1_SDA_AF_GPIO_MASK (0x1 << 7)
#define I2C1_SDA_AF_GPIO_INOUT

#define MAC0_MDIO_AF_GPIO 4
#define MAC0_MDIO_AF_GPIO_MASK (0x1 << 0)
#define MAC0_MDIO_AF_GPIO_INOUT

#define GPTIMER0_BRK_AF_GPIO 4
#define GPTIMER0_BRK_AF_GPIO_MASK (0x1 << 1)
#define GPTIMER0_BRK_AF_GPIO_INPUT

#define GPTIMER0_ETR_AF_GPIO 4
#define GPTIMER0_ETR_AF_GPIO_MASK (0x1 << 2)
#define GPTIMER0_ETR_AF_GPIO_INPUT

#define GPTIMER0_OCREF_CLR_AF_GPIO 4
#define GPTIMER0_OCREF_CLR_AF_GPIO_MASK (0x1 << 3)
#define GPTIMER0_OCREF_CLR_AF_GPIO_INPUT

#define GPTIMER1_BRK_AF_GPIO 4
#define GPTIMER1_BRK_AF_GPIO_MASK (0x1 << 4)
#define GPTIMER1_BRK_AF_GPIO_INPUT

#define GPTIMER1_ETR_AF_GPIO 4
#define GPTIMER1_ETR_AF_GPIO_MASK (0x1 << 5)
#define GPTIMER1_ETR_AF_GPIO_INPUT

#define SPI0_SCK_AF_GPIO 4
#define SPI0_SCK_AF_GPIO_MASK (0x1 << 5)
#define SPI0_SCK_AF_GPIO_OUTPUT

#define GPTIMER1_OCREF_CLR_AF_GPIO 4
#define GPTIMER1_OCREF_CLR_AF_GPIO_MASK (0x1 << 6)
#define GPTIMER1_OCREF_CLR_AF_GPIO_INPUT

#define SPI0_CSN_AF_GPIO 4
#define SPI0_CSN_AF_GPIO_MASK (0x1 << 6)
#define SPI0_CSN_AF_GPIO_OUTPUT

#define SPI1_SCK_AF_GPIO 4
#define SPI1_SCK_AF_GPIO_MASK (0x1 << 7)
#define SPI1_SCK_AF_GPIO_OUTPUT

#define GPTIMER2_BRK_AF_GPIO 4
#define GPTIMER2_BRK_AF_GPIO_MASK (0x1 << 7)
#define GPTIMER2_BRK_AF_GPIO_INPUT

#define SPI1_CSN_AF_GPIO 5
#define SPI1_CSN_AF_GPIO_MASK (0x1 << 0)
#define SPI1_CSN_AF_GPIO_OUTPUT

#define GPTIMER2_ETR_AF_GPIO 5
#define GPTIMER2_ETR_AF_GPIO_MASK (0x1 << 0)
#define GPTIMER2_ETR_AF_GPIO_INPUT

#define GPTIMER2_OCREF_CLR_AF_GPIO 5
#define GPTIMER2_OCREF_CLR_AF_GPIO_MASK (0x1 << 1)
#define GPTIMER2_OCREF_CLR_AF_GPIO_INPUT

#define GPTIMER0_CHN0_AF_GPIO 5
#define GPTIMER0_CHN0_AF_GPIO_MASK (0x1 << 1)
#define GPTIMER0_CHN0_AF_GPIO_OUTPUT

#define GPTIMER0_CHN1_AF_GPIO 5
#define GPTIMER0_CHN1_AF_GPIO_MASK (0x1 << 2)
#define GPTIMER0_CHN1_AF_GPIO_OUTPUT

#define GPTIMER0_CHN2_AF_GPIO 5
#define GPTIMER0_CHN2_AF_GPIO_MASK (0x1 << 3)
#define GPTIMER0_CHN2_AF_GPIO_OUTPUT

#define GPTIMER0_CHN3_AF_GPIO 5
#define GPTIMER0_CHN3_AF_GPIO_MASK (0x1 << 4)
#define GPTIMER0_CHN3_AF_GPIO_OUTPUT

#define GPTIMER3_BRK_AF_GPIO 5
#define GPTIMER3_BRK_AF_GPIO_MASK (0x1 << 2)
#define GPTIMER3_BRK_AF_GPIO_INPUT

#define GPTIMER3_ETR_AF_GPIO 5
#define GPTIMER3_ETR_AF_GPIO_MASK (0x1 << 3)
#define GPTIMER3_ETR_AF_GPIO_INPUT

#define GPTIMER3_OCREF_CLR_AF_GPIO 5
#define GPTIMER3_OCREF_CLR_AF_GPIO_MASK (0x1 << 4)
#define GPTIMER3_OCREF_CLR_AF_GPIO_INPUT

#define GPTIMER1_CHN0_AF_GPIO 5
#define GPTIMER1_CHN0_AF_GPIO_MASK (0x1 << 5)
#define GPTIMER1_CHN0_AF_GPIO_OUTPUT

#define GPTIMER1_CHN1_AF_GPIO 5
#define GPTIMER1_CHN1_AF_GPIO_MASK (0x1 << 6)
#define GPTIMER1_CHN1_AF_GPIO_OUTPUT

#define GPTIMER1_CHN2_AF_GPIO 5
#define GPTIMER1_CHN2_AF_GPIO_MASK (0x1 << 7)
#define GPTIMER1_CHN2_AF_GPIO_OUTPUT

#define GPTIMER1_CHN3_AF_GPIO 6
#define GPTIMER1_CHN3_AF_GPIO_MASK (0x1 << 0)
#define GPTIMER1_CHN3_AF_GPIO_OUTPUT

#define GPTIMER4_BRK_AF_GPIO 5
#define GPTIMER4_BRK_AF_GPIO_MASK (0x1 << 5)
#define GPTIMER4_BRK_AF_GPIO_INPUT

#define GPTIMER4_ETR_AF_GPIO 5
#define GPTIMER4_ETR_AF_GPIO_MASK (0x1 << 6)
#define GPTIMER4_ETR_AF_GPIO_INPUT

#define GPTIMER4_OCREF_CLR_AF_GPIO 5
#define GPTIMER4_OCREF_CLR_AF_GPIO_MASK (0x1 << 7)
#define GPTIMER4_OCREF_CLR_AF_GPIO_INPUT

#define UART0_NUARTCTS_AF_GPIO 6
#define UART0_NUARTCTS_AF_GPIO_MASK (0x1 << 0)
#define UART0_NUARTCTS_AF_GPIO_INPUT

#define UART0_UARTRXD_AF_GPIO 6
#define UART0_UARTRXD_AF_GPIO_MASK (0x1 << 1)
#define UART0_UARTRXD_AF_GPIO_INPUT

#define GPTIMER2_CHN0_AF_GPIO 6
#define GPTIMER2_CHN0_AF_GPIO_MASK (0x1 << 1)
#define GPTIMER2_CHN0_AF_GPIO_OUTPUT

#define GPTIMER2_CHN1_AF_GPIO 6
#define GPTIMER2_CHN1_AF_GPIO_MASK (0x1 << 2)
#define GPTIMER2_CHN1_AF_GPIO_OUTPUT

#define GPTIMER2_CHN2_AF_GPIO 6
#define GPTIMER2_CHN2_AF_GPIO_MASK (0x1 << 3)
#define GPTIMER2_CHN2_AF_GPIO_OUTPUT

#define GPTIMER2_CHN3_AF_GPIO 6
#define GPTIMER2_CHN3_AF_GPIO_MASK (0x1 << 4)
#define GPTIMER2_CHN3_AF_GPIO_OUTPUT

#define UART1_NUARTCTS_AF_GPIO 6
#define UART1_NUARTCTS_AF_GPIO_MASK (0x1 << 2)
#define UART1_NUARTCTS_AF_GPIO_INPUT

#define UART1_UARTRXD_AF_GPIO 6
#define UART1_UARTRXD_AF_GPIO_MASK (0x1 << 3)
#define UART1_UARTRXD_AF_GPIO_INPUT

#define UART2_NUARTCTS_AF_GPIO 6
#define UART2_NUARTCTS_AF_GPIO_MASK (0x1 << 4)
#define UART2_NUARTCTS_AF_GPIO_INPUT

#define UART2_UARTRXD_AF_GPIO 6
#define UART2_UARTRXD_AF_GPIO_MASK (0x1 << 5)
#define UART2_UARTRXD_AF_GPIO_INPUT

#define GPTIMER3_CHN0_AF_GPIO 6
#define GPTIMER3_CHN0_AF_GPIO_MASK (0x1 << 5)
#define GPTIMER3_CHN0_AF_GPIO_OUTPUT

#define GPTIMER3_CHN1_AF_GPIO 6
#define GPTIMER3_CHN1_AF_GPIO_MASK (0x1 << 6)
#define GPTIMER3_CHN1_AF_GPIO_OUTPUT

#define GPTIMER3_CHN2_AF_GPIO 6
#define GPTIMER3_CHN2_AF_GPIO_MASK (0x1 << 7)
#define GPTIMER3_CHN2_AF_GPIO_OUTPUT

#define GPTIMER3_CHN3_AF_GPIO 7
#define GPTIMER3_CHN3_AF_GPIO_MASK (0x1 << 0)
#define GPTIMER3_CHN3_AF_GPIO_OUTPUT

#define UART3_NUARTCTS_AF_GPIO 6
#define UART3_NUARTCTS_AF_GPIO_MASK (0x1 << 6)
#define UART3_NUARTCTS_AF_GPIO_INPUT

#define UART3_UARTRXD_AF_GPIO 6
#define UART3_UARTRXD_AF_GPIO_MASK (0x1 << 7)
#define UART3_UARTRXD_AF_GPIO_INPUT

#define UART4_NUARTCTS_AF_GPIO 7
#define UART4_NUARTCTS_AF_GPIO_MASK (0x1 << 0)
#define UART4_NUARTCTS_AF_GPIO_INPUT

#define UART4_UARTRXD_AF_GPIO 7
#define UART4_UARTRXD_AF_GPIO_MASK (0x1 << 1)
#define UART4_UARTRXD_AF_GPIO_INPUT

#define GPTIMER4_CHN0_AF_GPIO 7
#define GPTIMER4_CHN0_AF_GPIO_MASK (0x1 << 1)
#define GPTIMER4_CHN0_AF_GPIO_OUTPUT

#define GPTIMER4_CHN1_AF_GPIO 7
#define GPTIMER4_CHN1_AF_GPIO_MASK (0x1 << 2)
#define GPTIMER4_CHN1_AF_GPIO_OUTPUT

#define GPTIMER4_CHN2_AF_GPIO 7
#define GPTIMER4_CHN2_AF_GPIO_MASK (0x1 << 3)
#define GPTIMER4_CHN2_AF_GPIO_OUTPUT

#define GPTIMER4_CHN3_AF_GPIO 7
#define GPTIMER4_CHN3_AF_GPIO_MASK (0x1 << 4)
#define GPTIMER4_CHN3_AF_GPIO_OUTPUT

#define CAN0_INT_IN_AF_GPIO 7
#define CAN0_INT_IN_AF_GPIO_MASK (0x1 << 2)
#define CAN0_INT_IN_AF_GPIO_INPUT

#define CAN0_RX0_AF_GPIO 7
#define CAN0_RX0_AF_GPIO_MASK (0x1 << 3)
#define CAN0_RX0_AF_GPIO_INPUT

#define MAC0_PHY_INTB_AF_GPIO 7
#define MAC0_PHY_INTB_AF_GPIO_MASK (0x1 << 4)
#define MAC0_PHY_INTB_AF_GPIO_INPUT

#define UART0_NUARTRTS_AF_GPIO 7
#define UART0_NUARTRTS_AF_GPIO_MASK (0x1 << 5)
#define UART0_NUARTRTS_AF_GPIO_OUTPUT

#define MAC0_TX_CLK_AF_GPIO 7
#define MAC0_TX_CLK_AF_GPIO_MASK (0x1 << 5)
#define MAC0_TX_CLK_AF_GPIO_INPUT

#define UART0_UARTTXD_AF_GPIO 7
#define UART0_UARTTXD_AF_GPIO_MASK (0x1 << 6)
#define UART0_UARTTXD_AF_GPIO_OUTPUT

#define MAC0_RX_CLK_AF_GPIO 7
#define MAC0_RX_CLK_AF_GPIO_MASK (0x1 << 6)
#define MAC0_RX_CLK_AF_GPIO_INPUT

#define UART1_NUARTRTS_AF_GPIO 7
#define UART1_NUARTRTS_AF_GPIO_MASK (0x1 << 7)
#define UART1_NUARTRTS_AF_GPIO_OUTPUT

#define MAC0_RXD0_AF_GPIO 7
#define MAC0_RXD0_AF_GPIO_MASK (0x1 << 7)
#define MAC0_RXD0_AF_GPIO_INPUT

#define MAC0_RXD1_AF_GPIO 8
#define MAC0_RXD1_AF_GPIO_MASK (0x1 << 0)
#define MAC0_RXD1_AF_GPIO_INPUT

#define MAC0_RXD2_AF_GPIO 8
#define MAC0_RXD2_AF_GPIO_MASK (0x1 << 1)
#define MAC0_RXD2_AF_GPIO_INPUT

#define MAC0_RXD3_AF_GPIO 8
#define MAC0_RXD3_AF_GPIO_MASK (0x1 << 2)
#define MAC0_RXD3_AF_GPIO_INPUT

#define UART1_UARTTXD_AF_GPIO 8
#define UART1_UARTTXD_AF_GPIO_MASK (0x1 << 0)
#define UART1_UARTTXD_AF_GPIO_OUTPUT

#define UART2_NUARTRTS_AF_GPIO 8
#define UART2_NUARTRTS_AF_GPIO_MASK (0x1 << 1)
#define UART2_NUARTRTS_AF_GPIO_OUTPUT

#define UART2_UARTTXD_AF_GPIO 8
#define UART2_UARTTXD_AF_GPIO_MASK (0x1 << 2)
#define UART2_UARTTXD_AF_GPIO_OUTPUT

#define UART3_NUARTRTS_AF_GPIO 8
#define UART3_NUARTRTS_AF_GPIO_MASK (0x1 << 3)
#define UART3_NUARTRTS_AF_GPIO_OUTPUT

#define MAC0_RX_DV_AF_GPIO 8
#define MAC0_RX_DV_AF_GPIO_MASK (0x1 << 3)
#define MAC0_RX_DV_AF_GPIO_INPUT

#define MAC0_RX_ER_AF_GPIO 8
#define MAC0_RX_ER_AF_GPIO_MASK (0x1 << 4)
#define MAC0_RX_ER_AF_GPIO_INPUT

#define UART3_UARTTXD_AF_GPIO 8
#define UART3_UARTTXD_AF_GPIO_MASK (0x1 << 4)
#define UART3_UARTTXD_AF_GPIO_OUTPUT

#define UART4_NUARTRTS_AF_GPIO 8
#define UART4_NUARTRTS_AF_GPIO_MASK (0x1 << 5)
#define UART4_NUARTRTS_AF_GPIO_OUTPUT

#define MAC0_CRS_AF_GPIO 8
#define MAC0_CRS_AF_GPIO_MASK (0x1 << 5)
#define MAC0_CRS_AF_GPIO_INPUT

#define MAC0_COL_AF_GPIO 8
#define MAC0_COL_AF_GPIO_MASK (0x1 << 6)
#define MAC0_COL_AF_GPIO_INPUT

#define UART4_UARTTXD_AF_GPIO 8
#define UART4_UARTTXD_AF_GPIO_MASK (0x1 << 6)
#define UART4_UARTTXD_AF_GPIO_OUTPUT

#define CAN0_TX0_AF_GPIO 8
#define CAN0_TX0_AF_GPIO_MASK (0x1 << 7)
#define CAN0_TX0_AF_GPIO_OUTPUT

#define CAN0_TX1_AF_GPIO 9
#define CAN0_TX1_AF_GPIO_MASK (0x1 << 0)
#define CAN0_TX1_AF_GPIO_OUTPUT

#define MAC0_TXD0_AF_GPIO 9
#define MAC0_TXD0_AF_GPIO_MASK (0x1 << 1)
#define MAC0_TXD0_AF_GPIO_OUTPUT

#define MAC0_TXD1_AF_GPIO 9
#define MAC0_TXD1_AF_GPIO_MASK (0x1 << 2)
#define MAC0_TXD1_AF_GPIO_OUTPUT

#define MAC0_TXD2_AF_GPIO 9
#define MAC0_TXD2_AF_GPIO_MASK (0x1 << 3)
#define MAC0_TXD2_AF_GPIO_OUTPUT

#define MAC0_TXD3_AF_GPIO 9
#define MAC0_TXD3_AF_GPIO_MASK (0x1 << 4)
#define MAC0_TXD3_AF_GPIO_OUTPUT

#define MAC0_TX_EN_AF_GPIO 9
#define MAC0_TX_EN_AF_GPIO_MASK (0x1 << 5)
#define MAC0_TX_EN_AF_GPIO_OUTPUT

#define MAC0_TX_ER_AF_GPIO 9
#define MAC0_TX_ER_AF_GPIO_MASK (0x1 << 6)
#define MAC0_TX_ER_AF_GPIO_OUTPUT

#define MAC0_MDC_AF_GPIO 9
#define MAC0_MDC_AF_GPIO_MASK (0x1 << 7)
#define MAC0_MDC_AF_GPIO_OUTPUT

#endif
