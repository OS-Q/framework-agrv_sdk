#ifndef _AGM_CAN_H
#define _AGM_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

typedef struct 
{
  //         Register           Addr             Name                      Operating Mode  Reset Mode  Comment
  __IO uint32_t MOD;            // 0x00,         Mode                        Read/Write    Read/Write
  __O  uint32_t CMR;            // 0x04,         Command                     Write only    Write only  Returns 00h when read.
  __I  uint32_t SR;             // 0x08,         Status                      Read only     Read only
  __I  uint32_t IR;             // 0x0c,         Interrupt                   Read only     Read only
  __IO uint32_t IER;            // 0x10,         Interrupt enable            Read/Write    Read/Write
  __IO uint32_t RESERVED0;      // 0x14
  __IO uint32_t BTR0;           // 0x18,         Bus Timing 0                Read only     Read/Write
  __IO uint32_t BTR1;           // 0x1c,         Bus Timing 1                Read only     Read/Write
  __IO uint32_t OCR;            // 0x20,         Output Control              Read only     Read/Write
  __IO uint32_t RESERVED1[2];   // 0x24-0x28
  __I  uint32_t ALC;            // 0x2c,         Arbitration Lost Capture    Read only     Read only
  __I  uint32_t ECC;            // 0x30,         Error Code Capture          Read only     Read only
  __IO uint32_t EWLR;           // 0x34,         Error Warning Limit         Read only     Read/Write
  __IO uint32_t RXERR;          // 0x38,         Receive Error Counter       Read only     Read/Write
  __IO uint32_t TXERR;          // 0x3c,         Transmit Error Counter      Read only     Read/Write
  union {
    struct {                    // TX buffer
      __IO uint32_t TXFRAME;    // 0x40,         Transmit Frame Information  Write                     Read back from 0x180
      __IO uint32_t TXDATA[12]; // 0x44-0x70,    Transmit Data Information   Write                     Read back from 0x184-0x1B0
    };
    struct {                    // RX window
      __IO uint32_t RXFRAME;    // 0x40          Receive Frame Information   Read
      __IO uint32_t RXDATA[12]; // 0x44-0x70,    Receive Data Information    Read
    };
    struct {
      __IO uint32_t ACR[4];     // 0x40-0x4C,    Acceptance Code Registers                 Read/Write
      __IO uint32_t AMR[4];     // 0x50-0x5C,    Acceptance Mask Registers                 Read/Write
    };
  };
  __I  uint32_t RMC;            // 0x74,         Receive Message Counter     Read only     Read only
  __IO uint32_t RBSA;           // 0x78,         Receive Buffer Start Addr   Read only     Read/Write
  __IO uint32_t RESERVED2;      // 0x7C
  __IO uint32_t RXFIFO[64];     // 0x80h-0x17C,  Receive FIFO                Read only     Read/Write
  __I  uint32_t TXBUF[13];      // 0x180h-0x1B0, Transmit Buffer             Read only     Read only
} CAN_TypeDef;

#define CAN_MOD_RESET    (1 << 0) // Reset Mode
#define CAN_MOD_LISTONLY (1 << 1) // Listen Only Mode
#define CAN_MOD_SELFTEST (1 << 2) // Self Test Mode
#define CAN_MOD_AFM      (1 << 3) // Acceptance Filter Mode
#define CAN_MOD_SLEEP    (1 << 4) // Sleep Mode

#define CAN_CMR_TR  (1 << 0) // Transmission Request
#define CAN_CMR_AT  (1 << 1) // Abort Transmission
#define CAN_CMR_RRB (1 << 2) // Release Receive Buffer
#define CAN_CMR_CDO (1 << 3) // Clear Data Overrun
#define CAN_CMR_SRR (1 << 4) // Self Reception Request

#define CAN_SR_RBS (1 << 0) // Receive Buffer Status
#define CAN_SR_DOS (1 << 1) // Data Overrun Status
#define CAN_SR_TBS (1 << 2) // Transmit Buffer Status
#define CAN_SR_TCS (1 << 3) // Transmission Complete Status
#define CAN_SR_RS  (1 << 4) // Receive Status
#define CAN_SR_TS  (1 << 5) // Transmit Status
#define CAN_SR_ES  (1 << 6) // Error Status
#define CAN_SR_BS  (1 << 7) // Bus Status

#define CAN_IR_RI  (1 << 0) // Receive Interrupt
#define CAN_IR_TI  (1 << 1) // Transmit Interrupt
#define CAN_IR_EI  (1 << 2) // Error Warning Interrupt
#define CAN_IR_DOI (1 << 3) // Data Overrun Interrupt
#define CAN_IR_WUI (1 << 4) // Wake-Up Interrupt
#define CAN_IR_EPI (1 << 5) // Error Passive Interrupt
#define CAN_IR_ALI (1 << 6) // Arbitration Lost Interrupt
#define CAN_IR_BEI (1 << 7) // Bus Error Interrupt

#define CAN_BTR0_SJW_OFFSET 6

#define CAN_BTR0_BRP (0x3f << 0) // Baud Rate Prescaler
#define CAN_BTR0_SJW (0x3  << 6) // Synchronization Jump Width

#define CAN_BTR1_TSEG1_OFFSET 0
#define CAN_BTR1_TSEG2_OFFSET 4
#define CAN_BTR1_SAM_OFFSET 7

#define CAN_BTR1_TSEG1 (0xf << 0) // Time Segment 1, including propagation and phase 1
#define CAN_BTR1_TSEG2 (0x7 << 4) // Time Segment 2, including phase 2
#define CAN_BTR1_SAM   (0x1 << 7) // Sampling

#define CAN_ECC_ERROR_CODE_OFFSET 6
#define CAN_ECC_ERROR_DIR_OFFSET  5
#define CAN_ECC_ERROR_CODE (0x3 << CAN_ECC_ERROR_CODE_OFFSET)
#define CAN_ECC_ERROR_DIR  (0x1 << CAN_ECC_ERROR_DIR_OFFSET)

#define CAN_FRAME_FF  (1 << 7) // Frame format
#define CAN_FRAME_RTR (1 << 6) // Remote transmission request
#define CAN_FRAME_DLC 0x0f     // Data length code

#define CAN_CDR_CLOCK_OFF (1 << 3)

typedef enum
{
  CAN_FILTER_DUAL   = 0,
  CAN_FILTER_SINGLE = CAN_MOD_AFM,
} CAN_FilterModeTypeDef;

typedef enum
{
  CAN_SJW_1TQ = (0x0 << CAN_BTR0_SJW_OFFSET),
  CAN_SJW_2TQ = (0x1 << CAN_BTR0_SJW_OFFSET),
  CAN_SJW_3TQ = (0x2 << CAN_BTR0_SJW_OFFSET),
  CAN_SJW_4TQ = (0x3 << CAN_BTR0_SJW_OFFSET),
} Can_SyncJumpWidthTypeDef;

typedef enum
{
  CAN_TSEG1_1TQ  = (0x0 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_2TQ  = (0x1 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_3TQ  = (0x2 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_4TQ  = (0x3 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_5TQ  = (0x4 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_6TQ  = (0x5 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_7TQ  = (0x6 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_8TQ  = (0x7 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_9TQ  = (0x8 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_10TQ = (0x9 << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_11TQ = (0xa << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_12TQ = (0xb << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_13TQ = (0xc << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_14TQ = (0xd << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_15TQ = (0xe << CAN_BTR1_TSEG1_OFFSET),
  CAN_TSEG1_16TQ = (0xf << CAN_BTR1_TSEG1_OFFSET),
} CAN_TimeSeg1TypeDef;

typedef enum
{
  CAN_TSEG2_1TQ  = (0x0 << CAN_BTR1_TSEG2_OFFSET),
  CAN_TSEG2_2TQ  = (0x1 << CAN_BTR1_TSEG2_OFFSET),
  CAN_TSEG2_3TQ  = (0x2 << CAN_BTR1_TSEG2_OFFSET),
  CAN_TSEG2_4TQ  = (0x3 << CAN_BTR1_TSEG2_OFFSET),
  CAN_TSEG2_5TQ  = (0x4 << CAN_BTR1_TSEG2_OFFSET),
  CAN_TSEG2_6TQ  = (0x5 << CAN_BTR1_TSEG2_OFFSET),
  CAN_TSEG2_7TQ  = (0x6 << CAN_BTR1_TSEG2_OFFSET),
  CAN_TSEG2_8TQ  = (0x7 << CAN_BTR1_TSEG2_OFFSET),
} CAN_TimeSeg2TypeDef;

typedef enum
{
  CAN_SAMPLING_1 = 0,
  CAN_SAMPLING_3 = CAN_BTR1_SAM,
} CAN_SamplingTypeDef;

typedef enum
{
  CAN_OUTPUT_MODE_NORMAL = 0b10,
  CAN_OUTPUT_MODE_CLOCK  = 0b11,
} CAN_OutputModeTypeDef;

typedef enum
{
  CAN_STANDARD_FRAME_FORMAT  = 0,
  CAN_EXTENDTED_FRAME_FORMAT = CAN_FRAME_FF,
} CAN_FrameFormatTypeDef;

typedef enum
{
  CAN_DATA_FRAME   = 0,
  CAN_REMOTE_FRAME = CAN_FRAME_RTR,
} CAN_RemoteTypeDef;

typedef enum
{
  CAN_DATA_LENGTH_0 = 0,
  CAN_DATA_LENGTH_1 = 1,
  CAN_DATA_LENGTH_2 = 2,
  CAN_DATA_LENGTH_3 = 3,
  CAN_DATA_LENGTH_4 = 4,
  CAN_DATA_LENGTH_5 = 5,
  CAN_DATA_LENGTH_6 = 6,
  CAN_DATA_LENGTH_7 = 7,
  CAN_DATA_LENGTH_8 = 8,
} CAN_DataLengthTypeDef;

typedef enum
{
  CAN_ERROR_BIT   = (0x0 << CAN_ECC_ERROR_CODE_OFFSET),
  CAN_ERROR_FORM  = (0x1 << CAN_ECC_ERROR_CODE_OFFSET),
  CAN_ERROR_STUFF = (0x2 << CAN_ECC_ERROR_CODE_OFFSET),
  CAN_ERROR_OTHER = (0x3 << CAN_ECC_ERROR_CODE_OFFSET),
} CAN_ErrorCodeTypeDef;

typedef enum
{
  CAN_ERROR_TX = (0x0 << CAN_ECC_ERROR_DIR_OFFSET),
  CAN_ERROR_RX = (0x1 << CAN_ECC_ERROR_DIR_OFFSET),
} CAN_ErrorDirTypeDef;

static inline void CAN_EnableResetMode(CAN_TypeDef *can)  { can->MOD |=  CAN_MOD_RESET; }
static inline void CAN_DisableResetMode(CAN_TypeDef *can) { can->MOD &= ~CAN_MOD_RESET; }
static inline void CAN_EnableSleepMode(CAN_TypeDef *can)  { can->MOD |=  CAN_MOD_SLEEP; }
static inline void CAN_DisableSleepMode(CAN_TypeDef *can) { can->MOD &= ~CAN_MOD_SLEEP; }

static inline void CAN_StartTx(CAN_TypeDef *can)              { can->CMR |= CAN_CMR_TR; }
static inline void CAN_AbortTx(CAN_TypeDef *can)              { can->CMR |= CAN_CMR_AT; }
static inline void CAN_ReleaseRxBuffer(CAN_TypeDef *can)      { can->CMR |= CAN_CMR_RRB; } // Will clear CAN_IR_RI if no more data is is FIFO
static inline void CAN_ClearDataOverrun(CAN_TypeDef *can)     { can->CMR |= CAN_CMR_CDO; }

static inline void CAN_WaitForRx(CAN_TypeDef *can) { while (!(can->SR & CAN_SR_RBS)); }
static inline void CAN_WaitForTx(CAN_TypeDef *can) { while (!(can->SR & CAN_SR_TBS)); }
static inline bool CAN_IsErrorStatus(CAN_TypeDef *can) { return can->SR & CAN_SR_ES; }

// This will clear all interrupt bits except CAN_IR_RI
static inline uint32_t CAN_GetIntStatus(CAN_TypeDef *can) { return can->IR; }

static inline void CAN_EnableIntRx(CAN_TypeDef *can)  { can->IER |=  CAN_IR_RI; }
static inline void CAN_DisableIntRx(CAN_TypeDef *can) { can->IER &= ~CAN_IR_RI; }

static inline void CAN_EnableIntTx(CAN_TypeDef *can)  { can->IER |=  CAN_IR_TI; }
static inline void CAN_DisableIntTx(CAN_TypeDef *can) { can->IER &= ~CAN_IR_TI; }

static inline void CAN_EnableIntErrorWarning(CAN_TypeDef *can)  { can->IER |=  CAN_IR_EI; }
static inline void CAN_DisableIntErrorWarning(CAN_TypeDef *can) { can->IER &= ~CAN_IR_EI; }

static inline void CAN_EnableIntOverrun(CAN_TypeDef *can)  { can->IER |=  CAN_IR_DOI; }
static inline void CAN_DisableIntOverrun(CAN_TypeDef *can) { can->IER &= ~CAN_IR_DOI; }

static inline void CAN_EnableIntWakeup(CAN_TypeDef *can)  { can->IER |=  CAN_IR_WUI; }
static inline void CAN_DisableIntWakeup(CAN_TypeDef *can) { can->IER &= ~CAN_IR_WUI; }

static inline void CAN_EnableIntErrorPassive(CAN_TypeDef *can)  { can->IER |=  CAN_IR_EPI; }
static inline void CAN_DisableIntErrorPassive(CAN_TypeDef *can) { can->IER &= ~CAN_IR_EPI; }

static inline void CAN_EnableIntArbLost(CAN_TypeDef *can)  { can->IER |=  CAN_IR_ALI; }
static inline void CAN_DisableIntArbLost(CAN_TypeDef *can) { can->IER &= ~CAN_IR_ALI; }

static inline void CAN_EnableIntBusError(CAN_TypeDef *can)  { can->IER |=  CAN_IR_BEI; }
static inline void CAN_DisableIntBusError(CAN_TypeDef *can) { can->IER &= ~CAN_IR_BEI; }

static inline CAN_ErrorCodeTypeDef CAN_GetErrorCode(CAN_TypeDef *can) { return (CAN_ErrorCodeTypeDef)(can->ECC & CAN_ECC_ERROR_CODE); }
static inline CAN_ErrorDirTypeDef  CAN_GetErrorDir(CAN_TypeDef *can)  { return (CAN_ErrorDirTypeDef)(can->ECC & CAN_ECC_ERROR_DIR);   }

static inline void CAN_SetErrorWarningLimit(CAN_TypeDef *can, uint32_t limit) { can->EWLR = limit;  }
static inline void CAN_SetRxErrorCount     (CAN_TypeDef *can, uint32_t count) { can->RXERR = count; }
static inline void CAN_SetTxErrorCount     (CAN_TypeDef *can, uint32_t count) { can->TXERR = count; }

static inline uint32_t CAN_GetErrorWarningLimit(CAN_TypeDef *can) { return can->EWLR;  }
static inline uint32_t CAN_GetRxErrorCount     (CAN_TypeDef *can) { return can->RXERR; }
static inline uint32_t CAN_GetTxErrorCount     (CAN_TypeDef *can) { return can->TXERR; }
static inline uint32_t CAN_GetRxMessageCount   (CAN_TypeDef *can) { return can->RMC;   }

static inline uint32_t CAN_CalculatePrescaler(uint32_t freq, uint32_t baud_rate, CAN_TimeSeg1TypeDef tseg1, CAN_TimeSeg2TypeDef tseg2)
{
  return freq / baud_rate / 2 / ((tseg1 >> CAN_BTR1_TSEG1_OFFSET) + (tseg2 >> CAN_BTR1_TSEG2_OFFSET) + 3) - 1;
}

static inline uint32_t CAN_CalculateBaudRate(uint32_t freq, uint32_t prescaler, CAN_TimeSeg1TypeDef tseg1, CAN_TimeSeg2TypeDef tseg2)
{
  return freq / (prescaler + 1) / 2 / ((tseg1 >> CAN_BTR1_TSEG1_OFFSET) + (tseg2 >> CAN_BTR1_TSEG2_OFFSET) + 3);
}

typedef struct
{
  CAN_FilterModeTypeDef FilterMode;
  uint8_t               FilterMask[4];
  uint8_t               FilterCode[4];
} CAN_FilterConfigTypeDef;

typedef struct
{
  uint32_t                 Prescaler; // 0-63
  Can_SyncJumpWidthTypeDef SJW;
  CAN_TimeSeg1TypeDef      TSeg1;
  CAN_TimeSeg2TypeDef      TSeg2;
  CAN_SamplingTypeDef      Sampling;
  CAN_FilterConfigTypeDef  FilterConfig;
} CAN_InitTypeDef;

typedef struct
{
  uint32_t               ID; // Standard frame fromat: 11 bits, 0 - 0x7FF, Extended frame format: 29 bits, 0 - 0x1FFFFFFF
  CAN_FrameFormatTypeDef FF;
  CAN_RemoteTypeDef      RTR;
  CAN_DataLengthTypeDef  DLC;
  uint8_t                Data[8];
} CAN_TxMessageTypeDef;

#define CAN_RxMessageTypeDef CAN_TxMessageTypeDef

#define CAN_FILTER_DONT_CARE (-1)
#define CAN_FILTER_EXACT     (0)
void CAN_Filter_StructInit(CAN_FilterConfigTypeDef *init);
void CAN_SetStandardSingleFilter(CAN_FilterConfigTypeDef *init, uint16_t id_mask, uint16_t id_code,
                                 uint16_t data_mask, uint16_t data_code, uint8_t rtr_mask, uint8_t rtr_code);
void CAN_SetStandardDualFilter(CAN_FilterConfigTypeDef *init, uint16_t id_mask0, uint16_t id_code0,
                               uint8_t data_mask0, uint8_t data_code0, uint8_t rtr_mask0, uint8_t rtr_code0,
                               uint16_t id_mask1,  uint16_t id_code1,  uint8_t rtr_mask1, uint8_t rtr_code1);
void CAN_SetExtendedSingleFilter(CAN_FilterConfigTypeDef *init, uint32_t id_mask, uint32_t id_code,
                                 uint8_t rtr_mask, uint8_t rtr_code);
void CAN_SetExtendedDualFilter(CAN_FilterConfigTypeDef *init, uint32_t id_mask0, uint32_t id_code0,
                               uint32_t id_mask1, uint32_t id_code1);

void CAN_StructInit(CAN_InitTypeDef *init);
void CAN_Init(CAN_TypeDef *can, CAN_InitTypeDef *init);

void CAN_PrepareTx(CAN_TypeDef *can, CAN_TxMessageTypeDef *tx_msg);
void CAN_Transmit(CAN_TypeDef *can, CAN_TxMessageTypeDef *tx_msg);
void CAN_Receive(CAN_TypeDef *can, CAN_RxMessageTypeDef *rx_msg);

#ifdef __cplusplus
}
#endif

#endif
