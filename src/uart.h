#ifndef _AGM_UART_H
#define _AGM_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

typedef struct
{
	__IO uint32_t DR;          // 0x00, Data register
	__IO uint32_t RSR_ECR;     // 0x04, Receive status register/error clear register
	__IO uint32_t RESERVED[4]; // 0x08-0x14
	__I  uint32_t FR;          // 0x18, Flag register
	__IO uint32_t RESERVED1[2];// 0x1C-0x20
	__IO uint32_t IBRD;        // 0x24, Integer baud rate register
	__IO uint32_t FBRD;        // 0x28, Fractional baud rate register
	__IO uint32_t LCR_H;       // 0x2C, Line control register
	__IO uint32_t CR;          // 0x30, Control register
	__IO uint32_t IFLS;        // 0x34, Interrupt FIFO level select register
	__IO uint32_t IMSC;        // 0x38, Interrupt mask set/clear register
	__I  uint32_t RIS;         // 0x3C, Raw interrupt status register
	__I  uint32_t MIS;         // 0x40, Masked interrupt status register
	__O  uint32_t ICR;         // 0x44, Interrupt clear register
	__IO uint32_t DMACR;       // 0x48, DMA control register
} UART_TypeDef;

// Receive status and error clear flags
#define UART_RSR_ECR_FE (1 << 0) // Framing error
#define UART_RSR_ECR_PE (1 << 1) // Parity error
#define UART_RSR_ECR_BE (1 << 2) // Break error
#define UART_RSR_ECR_OE (1 << 3) // Overun error

// Receive status in DR
#define UART_DR_FE (UART_RSR_ECR_FE << 8)
#define UART_DR_PE (UART_RSR_ECR_PE << 8)
#define UART_DR_BE (UART_RSR_ECR_BE << 8)
#define UART_DR_OE (UART_RSR_ECR_OE << 8)

// Flag register
#define UART_FR_CTS  (1 << 0) // Clear to send
#define UART_FR_BUSY (1 << 3) // UART busy transmitting data
#define UART_FR_RXFE (1 << 4) // Receive FIFO empty
#define UART_FR_TXFF (1 << 5) // Transmit FIFO full
#define UART_FR_RXFF (1 << 6) // Receive FIFO full
#define UART_FR_TXFE (1 << 7) // Transmit FIFO empty

// Line control register
#define UART_LCR_BRK  (1 << 0) // Send break
#define UART_LCR_PEN  (1 << 1) // Parity enable
#define UART_LCR_EPS  (1 << 2) // Even parity select
#define UART_LCR_STP2 (1 << 3) // Two stop bits select
#define UART_LCR_FEN  (1 << 4) // Enable FIFOs
#define UART_LCR_SPS  (1 << 7) // Stick parity select

#define UART_LCR_WEN_OFFSET 5
#define UART_LCR_WLEN (3 << UART_LCR_WEN_OFFSET) // Word length, data bits in a frame

// Control register
#define UART_CR_UART_EN (1 << 0)  // UART enable
#define UART_CR_LBE     (1 << 7)  // Loop back enable
#define UART_CR_TXE     (1 << 8)  // Transmit enable
#define UART_CR_RXE     (1 << 9)  // Receive enable
#define UART_CR_RTS     (1 << 11) // Request to send
#define UART_CR_RTS_EN  (1 << 14) // RTS hardware flow control enable
#define UART_CR_CTS_EN  (1 << 15) // CTS hardware flow control enable

// Fifo level select
#define UART_TXIFLSEL_OFFEST 0 // Transmit interrupt FIFO level select
#define UART_RXIFLSEL_OFFEST 3 // Receive interrupt FIFO level select
#define UART_TXIFLSEL (7 << UART_TXIFLSEL_OFFEST)
#define UART_RXIFLSEL (7 << UART_RXIFLSEL_OFFEST)

// Interrupt flags, apply to IMSC, RIS, MIS and ICR
#define UART_INT_CTSM (1 << 1)  // nUARTCTS modem interrupt
#define UART_INT_RX   (1 << 4)  // Receive interrupt
#define UART_INT_TX   (1 << 5)  // Transmit interrupt
#define UART_INT_RT   (1 << 6)  // Receive timeout interrupt
#define UART_INT_FE   (1 << 7)  // Framing error interrupt
#define UART_INT_PE   (1 << 8)  // Parity error interrupt
#define UART_INT_BE   (1 << 9)  // Break error interrupt
#define UART_INT_OE   (1 << 10) // Overrun error interrupt
#define UART_INT_ALL  0x7ff     // All bits

// DMA control
#define UART_DMA_RX_EN  (1 << 0) // Receive DMA enable
#define UART_DMA_TX_EN  (1 << 1) // Transmit DMA enable
#define UART_DMA_ON_ERR (1 << 2) // Stop DMA on error

typedef enum
{
  UART_BAUDRATE_2000000 = 2000000,
  UART_BAUDRATE_1500000 = 1500000,
  UART_BAUDRATE_1000000 = 1000000,
  UART_BAUDRATE_921600  = 921600,
  UART_BAUDRATE_576000  = 576000,
  UART_BAUDRATE_500000  = 500000,
  UART_BAUDRATE_460800  = 460800,
  UART_BAUDRATE_230400  = 230400,
  UART_BAUDRATE_115200  = 115200,
  UART_BAUDRATE_57600   = 57600,
  UART_BAUDRATE_38400   = 38400,
  UART_BAUDRATE_19200   = 19200,
  UART_BAUDRATE_9600    = 9600,
  UART_BAUDRATE_4800    = 4800,
  UART_BAUDRATE_3600    = 3600,
  UART_BAUDRATE_2400    = 2400
} UART_BaudRateTypeDef;

typedef enum
{
  UART_LCR_PARITY_NONE = 0,
  UART_LCR_PARITY_ODD  = UART_LCR_PEN,
  UART_LCR_PARITY_EVEN = UART_LCR_PEN | UART_LCR_EPS,
  UART_LCR_PARITY_ONE  = UART_LCR_PEN | UART_LCR_SPS,
  UART_LCR_PARITY_ZERO = UART_LCR_PEN | UART_LCR_EPS | UART_LCR_SPS,
} UART_LCR_ParityTypeDef;

typedef enum
{
  UART_LCR_DATABITS_5 = (0 << UART_LCR_WEN_OFFSET),
  UART_LCR_DATABITS_6 = (1 << UART_LCR_WEN_OFFSET),
  UART_LCR_DATABITS_7 = (2 << UART_LCR_WEN_OFFSET),
  UART_LCR_DATABITS_8 = (3 << UART_LCR_WEN_OFFSET),
} UART_LCR_DataBitsTypeDef;

typedef enum
{
  UART_LCR_STOPBITS_1 = 0, 
  UART_LCR_STOPBITS_2 = UART_LCR_STP2,
} UART_LCR_StopBitsTypeDef;

typedef enum
{
  UART_LCR_FIFO_1  = 0, 
  UART_LCR_FIFO_16 = UART_LCR_FEN,
} UART_LCR_FifoTypeDef;

typedef enum
{
  UART_INT_FIFO_1_8TH = 0,
  UART_INT_FIFO_1_4TH = 1,
  UART_INT_FIFO_HALF  = 2,
  UART_INT_FIFO_3_4TH = 3,
  UART_INT_FIFO_7_8TH = 4,
} UART_IntFifoTypeDef;

typedef enum
{
  UART_DMA_NONE  = 0,
  UART_DMA_RX    = UART_DMA_RX_EN,
  UART_DMA_TX    = UART_DMA_TX_EN,
  UART_DMA_RX_TX = UART_DMA_RX_EN | UART_DMA_TX_EN,
} UART_DmaTypedef;

static inline void UART_TransmitData(UART_TypeDef *uart, uint8_t data) { uart->DR = data; }
static inline uint8_t UART_ReceiveData(UART_TypeDef *uart) { return uart->DR; }

static inline bool UART_IsFramingError(UART_TypeDef *uart) { return uart->RSR_ECR & UART_RSR_ECR_FE; }
static inline bool UART_IsParityError (UART_TypeDef *uart) { return uart->RSR_ECR & UART_RSR_ECR_PE; }
static inline bool UART_IsBreakError  (UART_TypeDef *uart) { return uart->RSR_ECR & UART_RSR_ECR_BE; }
static inline bool UART_IsOverrunError(UART_TypeDef *uart) { return uart->RSR_ECR & UART_RSR_ECR_OE; }

static inline void UART_ClearErrors(UART_TypeDef *uart) { uart->RSR_ECR = 0; } // Write any value to clear errors

static inline bool UART_IsCTS        (UART_TypeDef *uart) { return uart->FR & UART_FR_CTS;  } // Complement of nUARTCTS input pin
static inline bool UART_IsTxBusy     (UART_TypeDef *uart) { return uart->FR & UART_FR_BUSY; }
static inline bool UART_IsRxFifoEmpty(UART_TypeDef *uart) { return uart->FR & UART_FR_RXFE; }
static inline bool UART_IsTxFifoFull (UART_TypeDef *uart) { return uart->FR & UART_FR_TXFF; }
static inline bool UART_IsRxFifoFull (UART_TypeDef *uart) { return uart->FR & UART_FR_RXFF; }
static inline bool UART_IsTxFifoEmpty(UART_TypeDef *uart) { return uart->FR & UART_FR_TXFE; }

static inline void UART_SendBreak (UART_TypeDef *uart) { uart->LCR_H |=  UART_LCR_BRK; }
static inline void UART_ClearBreak(UART_TypeDef *uart) { uart->LCR_H &= ~UART_LCR_BRK; }

static inline void UART_SetParity   (UART_TypeDef *uart, UART_LCR_ParityTypeDef parity) { MODIFY_BIT(uart->LCR_H, UART_LCR_PARITY_ZERO, parity); }
static inline void UART_SetStopBits (UART_TypeDef *uart, UART_LCR_StopBitsTypeDef stop) { MODIFY_BIT(uart->LCR_H, UART_LCR_STP2, stop); }
static inline void UART_SetFifoLevel(UART_TypeDef *uart, UART_LCR_FifoTypeDef fifo)     { MODIFY_BIT(uart->LCR_H, UART_LCR_FEN, fifo); }
static inline void UART_SetDataBits (UART_TypeDef *uart, UART_LCR_DataBitsTypeDef len)  { MODIFY_BIT(uart->LCR_H, UART_LCR_WLEN, len); }

static inline UART_LCR_ParityTypeDef   UART_GetParity   (UART_TypeDef *uart) { return (UART_LCR_ParityTypeDef)(uart->LCR_H & UART_LCR_PARITY_ZERO); }
static inline UART_LCR_StopBitsTypeDef UART_GetStopBits (UART_TypeDef *uart) { return (UART_LCR_StopBitsTypeDef)(uart->LCR_H & UART_LCR_STP2); }
static inline UART_LCR_FifoTypeDef     UART_GetFifoLevel(UART_TypeDef *uart) { return (UART_LCR_FifoTypeDef)(uart->LCR_H & UART_LCR_FEN); }
static inline UART_LCR_DataBitsTypeDef UART_GetDataBits (UART_TypeDef *uart) { return (UART_LCR_DataBitsTypeDef)(uart->LCR_H & UART_LCR_WLEN); }

static inline void UART_Enable         (UART_TypeDef *uart) { uart->CR |=  UART_CR_UART_EN;}
static inline void UART_Disable        (UART_TypeDef *uart) { uart->CR &= ~UART_CR_UART_EN;}
static inline void UART_EnableLoopBack (UART_TypeDef *uart) { uart->CR |=  UART_CR_LBE;    }
static inline void UART_DisableLoopBack(UART_TypeDef *uart) { uart->CR &= ~UART_CR_LBE;    }
static inline void UART_SetRTS         (UART_TypeDef *uart) { uart->CR |=  UART_CR_RTS;    } // Set nUARTRTS to 0 (active)
static inline void UART_ClearRTS       (UART_TypeDef *uart) { uart->CR &= ~UART_CR_RTS;    } // Set nUARTRTS to 1 (inactive)
static inline void UART_EnableRTS      (UART_TypeDef *uart) { uart->CR |=  UART_CR_RTS_EN; }
static inline void UART_DisableRTS     (UART_TypeDef *uart) { uart->CR &= ~UART_CR_RTS_EN; }
static inline void UART_EnableCTS      (UART_TypeDef *uart) { uart->CR |=  UART_CR_CTS_EN; }
static inline void UART_DisableCTS     (UART_TypeDef *uart) { uart->CR &= ~UART_CR_CTS_EN; }

static inline bool UART_IsEnabled      (UART_TypeDef *uart) { return uart->CR & UART_CR_UART_EN; }

static inline void UART_SetTxIntFifoLevel(UART_TypeDef *uart, UART_IntFifoTypeDef level) { MODIFY_BIT(uart->IFLS, UART_TXIFLSEL, level << UART_TXIFLSEL_OFFEST); }
static inline void UART_SetRxIntFifoLevel(UART_TypeDef *uart, UART_IntFifoTypeDef level) { MODIFY_BIT(uart->IFLS, UART_RXIFLSEL, level << UART_RXIFLSEL_OFFEST); }

static inline void UART_EnableInt (UART_TypeDef *uart, uint32_t bits) { uart->IMSC  |=  bits; }
static inline void UART_DisableInt(UART_TypeDef *uart, uint32_t bits) { uart->IMSC  &= ~bits; }
static inline void UART_ClearInt  (UART_TypeDef *uart, uint32_t bits) { uart->ICR    =  bits; }

// Can check multiple interrupts in one call. Will return true if any bit is active
static inline bool UART_IsRawIntActive   (UART_TypeDef *uart, uint32_t bits) { return uart->RIS & bits; }
static inline bool UART_IsMaskedIntActive(UART_TypeDef *uart, uint32_t bits) { return uart->MIS & bits; }

static inline void UART_SetDmaMode(UART_TypeDef *uart, UART_DmaTypedef mode) { MODIFY_BIT(uart->DMACR, UART_DMA_TX_EN | UART_DMA_RX_EN, mode); }

static inline void UART_EnableDmaOnError (UART_TypeDef *uart) { uart->DMACR |=  UART_DMA_ON_ERR; }
static inline void UART_DisableDmaOnError(UART_TypeDef *uart) { uart->DMACR &= ~UART_DMA_ON_ERR; }

void UART_Init(UART_TypeDef             *uart,
               UART_BaudRateTypeDef     baudrate,
               UART_LCR_DataBitsTypeDef databits,
               UART_LCR_StopBitsTypeDef stopbits,
               UART_LCR_ParityTypeDef   parity,
               UART_LCR_FifoTypeDef     fifo);

void UART_InitBaud(UART_TypeDef             *uart,
                   uint32_t                 integer_baud,
                   uint32_t                 fractional_baud,
                   UART_LCR_DataBitsTypeDef databits,
                   UART_LCR_StopBitsTypeDef stopbits,
                   UART_LCR_ParityTypeDef   parity,
                   UART_LCR_FifoTypeDef     fifo);

void UART_DeInit(UART_TypeDef *uart);
void UART_SetBaudRate(UART_TypeDef *uart, UART_BaudRateTypeDef baudrate);

ReturnCodeTypedef UART_SendCh(UART_TypeDef *uart, unsigned char ch);
ReturnCodeTypedef UART_Send(UART_TypeDef *uart, const unsigned char *p, unsigned int num);
unsigned int      UART_ReceiveCh(UART_TypeDef *uart, unsigned char *ch, unsigned int timeout); // timeout in ms
unsigned int      UART_Receive(UART_TypeDef *uart, unsigned char *p, unsigned int num, unsigned int timeout);

extern UART_TypeDef *MSG_UART;

#ifdef __cplusplus
}
#endif

#endif
