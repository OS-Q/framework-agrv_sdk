#include "util.h"
#include "gpio.h"
#include "uart.h"
#include "system.h"
#include "interrupt.h"
#include "peripherals.h"

uint64_t UTIL_UsToMcycle(uint32_t us)
{
  return (uint64_t)us * (SYS_GetSysClkFreq() / 1000000);
}

uint32_t UTIL_McycleToUs(uint64_t mcycle)
{
  return mcycle * 1000000 / SYS_GetSysClkFreq();
}

uint32_t UTIL_GetTick(void) // In millisecond
{
  return UTIL_GetMcycle() * 1000 / SYS_GetSysClkFreq();
}

void UTIL_IdleUs(uint32_t us)
{
  volatile uint64_t mcycle = UTIL_GetMcycle() + UTIL_UsToMcycle(us);
  while (UTIL_GetMcycle() < mcycle);
}

uint8_t UTIL_ReverseBits(uint8_t b)
{
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

uint16_t UTIL_ReverseBytes2(uint16_t i)
{
  return (uint16_t)((i << 8) | (i >> 8));
}

uint32_t UTIL_ReverseBytes4(uint32_t i)
{
  return (uint32_t)((i << 24) | ((i << 8) & 0x00ff0000) | ((i >> 8) & 0x0000ff00) | (i >> 24));
}

extern void *memalign (size_t align, size_t sz);
void* AlignedMalloc(size_t alignment, size_t required_bytes)
{
#ifdef DEFINE_MEMALIGN
  return memalign(alignment, required_bytes);
#else
  void* p1; // original block
  void** p2; // aligned block
  int offset = alignment - 1 + sizeof(void*);
  if ((p1 = (void*)malloc(required_bytes + offset)) == NULL) {
    return NULL;
  }
  p2 = (void**)(((size_t)(p1) + offset) & ~(alignment - 1));
  p2[-1] = p1;
  return p2;
#endif
}

void AlignedFree(void *p)
{
#ifdef DEFINE_MEMALIGN
  free((void *)p);
#else
  if (p) {
    free(((void**)p)[-1]);
  }
#endif
}

__attribute__((weak)) UART_TypeDef *MSG_UART; // MSG_UART must be initialized before using uart_printf

void UART_PutChar(int c, void **putdat)
{
  UART_SendCh(MSG_UART, c);
}

int uart_printf(const char *format, ...)
{
  va_list ap;
  va_start(ap, format);
  vprintfmt(UART_PutChar, NULL, format, ap, 0);
  va_end(ap);
  return 0;
}

// Provide a customized putchar function
#ifdef LOGGER_UART
bool UTIL_StartLogger()
{
  PERIPHERAL_ENABLE_(UART, LOGGER_UART);
  UART_Init(UARTx(LOGGER_UART), LOGGER_BAUD_RATE,
            UART_LCR_DATABITS_8, UART_LCR_STOPBITS_1,
            UART_LCR_PARITY_NONE, UART_LCR_FIFO_1);
  dbg_printf("LOGGER_UART: Uart%d\n", LOGGER_UART);
  return true;
}

bool UTIL_StopLogger()
{
  PERIPHERAL_DISABLE_(UART, LOGGER_UART);
  UART_DeInit(UARTx(LOGGER_UART));
  return true;
}

#undef putchar
int putchar(int ch)
{
  return UART_SendCh(UARTx(LOGGER_UART), ch);
}

#elif defined(SEGGER_RTT)
#include "segger/RTT/SEGGER_RTT.h"
bool UTIL_StartLogger()
{
  return true;
}
bool UTIL_StopLogger()
{
  return true;
}
#undef putchar
int putchar(int ch)
{
  return SEGGER_RTT_PutChar(0, ch);
}

#else
__attribute__((weak)) bool UTIL_StartLogger()
{
  return true;
}
__attribute__((weak)) bool UTIL_StopLogger()
{
  return true;
}

#endif

