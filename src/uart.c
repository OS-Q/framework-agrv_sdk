#include "system.h"
#include "gpio.h"
#include "uart.h"

void UART_Init(UART_TypeDef             *uart,
               UART_BaudRateTypeDef     baudrate,
               UART_LCR_DataBitsTypeDef databits,
               UART_LCR_StopBitsTypeDef stopbits,
               UART_LCR_ParityTypeDef   parity,
               UART_LCR_FifoTypeDef     fifo)
{
  uint32_t pclk = SYS_GetPclkFreq();
  uint32_t ibrd  = pclk / baudrate / 16;
  uint32_t fbrd = pclk - ibrd * baudrate * 16;
  fbrd = (fbrd * 4 + baudrate / 2) / baudrate;
  if (fbrd >= 64) {
    ++ibrd;
    fbrd = 0;
  }

  UART_InitBaud(uart, ibrd, fbrd, databits, stopbits, parity, fifo);
}

void UART_InitBaud(UART_TypeDef             *uart,
                   uint32_t                 integer_baud,
                   uint32_t                 fractional_baud,
                   UART_LCR_DataBitsTypeDef databits,
                   UART_LCR_StopBitsTypeDef stopbits,
                   UART_LCR_ParityTypeDef   parity,
                   UART_LCR_FifoTypeDef     fifo)
{
  uart->CR    = 0x0; // Disable uart
  uart->IBRD  = integer_baud;
  uart->FBRD  = fractional_baud;
  uart->LCR_H = databits | stopbits | parity | fifo;
  uart->ICR   = 0x7ff; // Clear all interrupts
  uart->IMSC  = 0; // Disable all interrupts
  uart->CR    = UART_CR_UART_EN | UART_CR_RXE | UART_CR_TXE;
  uart->DMACR = 0x0; // No DMA
}

void UART_DeInit(UART_TypeDef *uart)
{
  uart->CR    = 0x0;
  uart->ICR   = 0x0;
  uart->IMSC  = 0x0;
  uart->DMACR = 0x0;
}

void UART_SetBaudRate(UART_TypeDef *uart, UART_BaudRateTypeDef baudrate)
{
  uint32_t pclk = SYS_GetPclkFreq();
  uint32_t ibrd  = pclk / baudrate / 16;
  uint32_t fbrd = pclk - ibrd * baudrate * 16;
  fbrd = (fbrd * 4 + baudrate / 2) / baudrate;
  uart->IBRD = ibrd;
  uart->FBRD = fbrd;
}

ReturnCodeTypedef UART_Send(UART_TypeDef *uart, const unsigned char *p, unsigned int num)
{
  for (unsigned int i = 0; i < num; ++i) {
    while (UART_IsTxFifoFull(uart));
    uart->DR = *p++;
  }
  return RET_OK;
}

ReturnCodeTypedef UART_SendCh(UART_TypeDef *uart, unsigned char ch)
{
  return UART_Send(uart, &ch, 1);
}

unsigned int UART_Receive(UART_TypeDef *uart, unsigned char *p, unsigned int num, unsigned int timeout)
{
  unsigned int cnt = 0;
  uint32_t tick = UTIL_GetTick();
  while (cnt < num) {
    if (UART_IsRxFifoEmpty(uart)) {
      if (timeout && UTIL_GetTick() - tick > timeout) {
        break;
      } else {
        continue;
      }
    }
    *p++ = uart->DR;
    ++cnt;
  }
  return cnt;
}

unsigned int UART_ReceiveCh(UART_TypeDef *uart, unsigned char *ch, unsigned int timeout)
{
  return UART_Receive(uart, ch, 1, timeout);
}
