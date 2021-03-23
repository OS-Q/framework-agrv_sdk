#ifndef _AGM_DMAC_H
#define _AGM_DMAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

#define DMAC_CHANNELS 8
#define DMAC DMAC0      // This is the only DMAC supported for now

// For channel control register
#define DMAC_TRANSFER_SIZE_OFFSET 0
#define DMAC_MAX_TRANSFER_SIZE    ((1 << 12) - 1)
#define DMAC_SRC_BURST_OFFSET     12
#define DMAC_DST_BURST_OFFSET     15
#define DMAC_SRC_WIDTH_OFFSET     18
#define DMAC_DST_WIDTH_OFFSET     21
#define DMAC_SRC_MASTER_OFFSET    24
#define DMAC_DST_MASTER_OFFSET    25
#define DMAC_SRC_ADDR_INCR_OFFSET 26
#define DMAC_DST_ADDR_INCR_OFFSET 27
#define DMAC_TC_INT_ENABLE_OFFSET 31

// For channel configuration register
#define DMAC_ENABLE_OFFSET         0
#define DMAC_SRC_PERIPHERAL_OFFSET 1
#define DMAC_DST_PERIPHERAL_OFFSET 6
#define DMAC_FLOW_CONTROL_OFFSET   11
#define DMAC_INT_ERROR_MASK_OFFSET 14
#define DMAC_INT_TC_MASK_OFFSET    15
#define DMAC_CHANNEL_ACTIVE_OFFSET 17
#define DMAC_CHANNEL_HALT_OFFSET   18

#define DMAC_TRANSFER_SIZE_MASK DMAC_MAX_TRANSFER_SIZE
#define DMAC_BURST_MASK         0x7
#define DMAC_WIDTH_MASK         0x7
#define DMAC_ADDR_INCR_MASK     0x1
#define DMAC_PERIPHERAL_MASK    0xf
#define DMAC_FLOW_CONTROL_MASK  0x7
#define DMAC_TC_INT_ENABLE_MASK 0x7

typedef struct
{
  __IO uint32_t SrcAddr;       // 0x00, Channel Source Address Register
  __IO uint32_t DstAddr;       // 0x04, Channel Destination Address Register
  __IO uint32_t LLI;           // 0x08, Channel Linked List Item Register
  __IO uint32_t Control;       // 0x0C, Channel Control Register
  __IO uint32_t Configuration; // 0x10, Channel Configuration Register
  __IO uint32_t Reserved[3];   // 0x14-0x1C
} DMAC_ChannelTypeDef;

typedef volatile struct
{
  __I  uint32_t IntStatus;         // 0x000, Interrupt Status Register
  __I  uint32_t IntTCStatus;       // 0x004, Interrupt Terminal Count Status Register
  __O  uint32_t IntTCClear;        // 0x008, Interrupt Terminal Count Clear Register
  __I  uint32_t IntErrorStatus;    // 0x00C, Interrupt Error Status Register
  __O  uint32_t IntErrorClear;     // 0x010, Interrupt Error Clear Register
  __I  uint32_t RawIntTCStatus;    // 0x014, Raw Interrupt Terminal Count Status Register
  __I  uint32_t RawIntErrorStatus; // 0x018, Raw Error Interrupt Status Register
  __I  uint32_t EnabledChannels;   // 0x01C, Enabled Channel Register
  __IO uint32_t SoftBReq;          // 0x020, Software Burst Request Register
  __IO uint32_t SoftSReq;          // 0x024, Software Single Request Register
  __IO uint32_t SoftLBReq;         // 0x028, Software Last Burst Request Register
  __IO uint32_t SoftSBReq;         // 0x02C, Software Last Single Request Register
  __IO uint32_t Configuration;     // 0x030, Configuration Register
  __IO uint32_t Sync;              // 0x034, Synchronization Register
  __IO uint32_t Reserved[(0x100 - 0x038) >> 2];
  __IO DMAC_ChannelTypeDef Channels[DMAC_CHANNELS]; // 0x100, Channel Registers
} DMAC_TypeDef;

// Get channel number from DMAC_ChannelTypeDef*
#define DMAC_CHANNEL_NUM(__ch) (__ch - &DMAC->Channels[0])

typedef struct
{
  __IO uint32_t SrcAddr;
  __IO uint32_t DstAddr;
  __IO uint32_t LLI;
  __IO uint32_t Control;
} DMAC_LLI_TypeDef;

typedef enum
{
  DMAC_BURST_1   = 0,
  DMAC_BURST_4   = 1,
  DMAC_BURST_8   = 2,
  DMAC_BURST_16  = 3,
  DMAC_BURST_32  = 4,
  DMAC_BURST_64  = 5,
  DMAC_BURST_128 = 6,
  DMAC_BURST_256 = 7,
} DMAC_BurstTypeDef;

typedef enum
{
  DMAC_WIDTH_8_BIT  = 0,
  DMAC_WIDTH_16_BIT = 1,
  DMAC_WIDTH_32_BIT = 2,
} DMAC_WidthTypeDef;

typedef enum
{
  DMAC_ADDR_INCR_OFF = 0, // Address will not increment after each transfer
  DMAC_ADDR_INCR_ON  = 1, // Address will increment after each transfer
} DMAC_AddrIncTypeDef;

typedef enum
{
  DMAC_AHB_M1 = 0,
  DMAC_AHB_M2 = 1,
} DMAC_AHBMasterTypeDef;

typedef enum
{
  DMAC_CHANNEL0 = 0,
  DMAC_CHANNEL1 = 1,
  DMAC_CHANNEL2 = 2,
  DMAC_CHANNEL3 = 3,
  DMAC_CHANNEL4 = 4,
  DMAC_CHANNEL5 = 5,
  DMAC_CHANNEL6 = 6,
  DMAC_CHANNEL7 = 7,
} DMAC_ChannelNumTypeDef;

typedef enum
{
  DMAC_MEM_TO_MEM_DMA_CTRL                          = 0,
  DMAC_MEM_TO_PERIPHERAL_DMA_CTRL                   = 1,
  DMAC_PERIPHERAL_TO_MEM_DMA_CTRL                   = 2,
  DMAC_PERIPHERAL_TO_PERIPHERAL_DMA_CTRL            = 3,
  DMAC_PERIPHERAL_TO_PERIPHERAL_DST_PERIPHERAL_CTRL = 4,
  DMAC_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL            = 5,
  DMAC_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL            = 6,
  DMAC_PERIPHERAL_TO_PERIPHERAL_SRC_PERIPHERAL_CTRL = 7,
} DMAC_FlowControlTypeDef;

typedef enum
{
  DMAC_M1_LITTLE_ENDIAN = 0 << 1,
  DMAC_M1_BIG_ENDIAN    = 1 << 1,
  DMAC_M2_LITTLE_ENDIAN = 0 << 2,
  DMAC_M2_BIG_ENDIAN    = 1 << 2,
} DMAC_EndianTypeDef;

static inline uint32_t DMAC_MakeControl(DMAC_AddrIncTypeDef srcIncr, DMAC_AddrIncTypeDef dstIncr,
                                        DMAC_WidthTypeDef srcWidth, DMAC_WidthTypeDef dstWidth,
                                        DMAC_BurstTypeDef srcBurst, DMAC_BurstTypeDef dstBurst,
                                        uint32_t transferSize, EnableTypeDef enableIntTC)
{
  return ((transferSize & DMAC_TRANSFER_SIZE_MASK) << DMAC_TRANSFER_SIZE_OFFSET |
          (srcBurst    &  DMAC_BURST_MASK)         << DMAC_SRC_BURST_OFFSET     |
          (dstBurst    &  DMAC_BURST_MASK)         << DMAC_DST_BURST_OFFSET     |
          (srcWidth    &  DMAC_WIDTH_MASK)         << DMAC_SRC_WIDTH_OFFSET     |
          (dstWidth    &  DMAC_WIDTH_MASK)         << DMAC_DST_WIDTH_OFFSET     |
          DMAC_AHB_M1                              << DMAC_SRC_MASTER_OFFSET    |
          DMAC_AHB_M2                              << DMAC_DST_MASTER_OFFSET    |
          (srcIncr     &  DMAC_ADDR_INCR_MASK)     << DMAC_SRC_ADDR_INCR_OFFSET |
          (dstIncr     &  DMAC_ADDR_INCR_MASK)     << DMAC_DST_ADDR_INCR_OFFSET |
          (enableIntTC &  DMAC_TC_INT_ENABLE_MASK) << DMAC_TC_INT_ENABLE_OFFSET);
}

static inline uint32_t DMAC_MakeConfiguration(DMAC_FlowControlTypeDef transferType, uint32_t srcPeripheral, uint32_t dstPeripheral)
{
  return (ENABLE                                       << DMAC_ENABLE_OFFSET         |
          (srcPeripheral &  DMAC_PERIPHERAL_MASK)      << DMAC_SRC_PERIPHERAL_OFFSET |
          (dstPeripheral &  DMAC_PERIPHERAL_MASK)      << DMAC_DST_PERIPHERAL_OFFSET |
          (transferType  &  DMAC_FLOW_CONTROL_MASK)    << DMAC_FLOW_CONTROL_OFFSET   |
          ENABLE                                       << DMAC_INT_ERROR_MASK_OFFSET |
          ENABLE                                       << DMAC_INT_TC_MASK_OFFSET);
}

void DMAC_Init(void);

void DMAC_Config(DMAC_ChannelNumTypeDef channel, uint32_t srcAddr, uint32_t dstAddr,
                 DMAC_AddrIncTypeDef srcIncr, DMAC_AddrIncTypeDef dstIncr,
                 DMAC_WidthTypeDef srcWidth, DMAC_WidthTypeDef dstWidth,
                 DMAC_BurstTypeDef srcBurst, DMAC_BurstTypeDef dstBurst,
                 uint32_t transferSize, DMAC_FlowControlTypeDef transferType,
                 uint32_t srcPeripheral, uint32_t dstPeripheral);

void DMAC_ConfigLLI(DMAC_ChannelNumTypeDef channel, DMAC_FlowControlTypeDef transferType,
                    uint32_t srcPeripheral, uint32_t dstPeripheral, uint32_t lli);

void DMAC_ConfigCircular(DMAC_ChannelNumTypeDef channel, uint32_t srcAddr, uint32_t dstAddr,
                         DMAC_AddrIncTypeDef srcIncr, DMAC_AddrIncTypeDef dstIncr,
                         DMAC_WidthTypeDef srcWidth, DMAC_WidthTypeDef dstWidth,
                         DMAC_BurstTypeDef srcBurst, DMAC_BurstTypeDef dstBurst,
                         uint32_t transferSize, DMAC_FlowControlTypeDef transferType,
                         uint32_t srcPeripheral, uint32_t dstPeripheral, DMAC_LLI_TypeDef *lli);

DMAC_LLI_TypeDef *DMAC_AutoTransfer(DMAC_ChannelNumTypeDef channel, uint32_t srcAddr, uint32_t dstAddr,
                                    DMAC_AddrIncTypeDef srcIncr, DMAC_AddrIncTypeDef dstIncr,
                                    DMAC_WidthTypeDef srcWidth, DMAC_WidthTypeDef dstWidth,
                                    DMAC_BurstTypeDef srcBurst, DMAC_BurstTypeDef dstBurst,
                                    uint32_t transferSize, DMAC_FlowControlTypeDef transferType,
                                    uint32_t srcPeripheral, uint32_t dstPeripheral,
                                    EnableTypeDef enableIntTC, DMAC_LLI_TypeDef *lli_arr);

void DMAC_WaitedTransfer(DMAC_ChannelNumTypeDef channel, uint32_t srcAddr, uint32_t dstAddr,
                         DMAC_AddrIncTypeDef srcIncr, DMAC_AddrIncTypeDef dstIncr,
                         DMAC_WidthTypeDef srcWidth, DMAC_WidthTypeDef dstWidth,
                         DMAC_BurstTypeDef srcBurst, DMAC_BurstTypeDef dstBurst,
                         uint32_t transferSize, DMAC_FlowControlTypeDef transferType,
                         uint32_t srcPeripheral, uint32_t dstPeripheral);

static inline void DMAC_EnableChannel(DMAC_ChannelNumTypeDef channel)  { DMAC->Channels[channel].Configuration |= ENABLE; }
static inline void DMAC_DisableChannel(DMAC_ChannelNumTypeDef channel) { DMAC->Channels[channel].Configuration &= ~ENABLE; } // May lose data in FIFO
static inline bool DMAC_IsEnabledChannel(DMAC_ChannelNumTypeDef channel) { return DMAC->EnabledChannels & (1 << channel); }
static inline void DMAC_WaitChannel(DMAC_ChannelNumTypeDef channel) { while (DMAC_IsEnabledChannel(channel)); }
void DMAC_HaltChannel(DMAC_ChannelNumTypeDef channel);

static inline void DMAC_ClearIntError(void) { DMAC->IntErrorClear = 0xff; }
static inline void DMAC_ClearIntTC   (void) { DMAC->IntTCClear    = 0xff; }

static inline void DMAC_ClearChannelIntError(DMAC_ChannelNumTypeDef channel) { DMAC->IntErrorClear = 1 << channel; }
static inline void DMAC_ClearChannelIntTC   (DMAC_ChannelNumTypeDef channel) { DMAC->IntTCClear    = 1 << channel; }

static inline uint8_t DMAC_IsMaskedIntActive     (void) { return DMAC->IntStatus;         }
static inline uint8_t DMAC_IsMaskedIntTCActive   (void) { return DMAC->IntTCStatus;       }
static inline uint8_t DMAC_IsMaskedIntErrorActive(void) { return DMAC->IntErrorStatus;    }
static inline uint8_t DMAC_IsRawIntTCActive      (void) { return DMAC->RawIntTCStatus;    }
static inline uint8_t DMAC_IsRawIntErrorActive   (void) { return DMAC->RawIntErrorStatus; }

static inline bool DMAC_IsChannelMaskedIntActive     (DMAC_ChannelNumTypeDef channel) { return DMAC->IntStatus         & (1 << channel); }
static inline bool DMAC_IsChannelMaskedIntTCActive   (DMAC_ChannelNumTypeDef channel) { return DMAC->IntTCStatus       & (1 << channel); }
static inline bool DMAC_IsChannelMaskedIntErrorActive(DMAC_ChannelNumTypeDef channel) { return DMAC->IntErrorStatus    & (1 << channel); }
static inline bool DMAC_IsChannelRawIntTCActive      (DMAC_ChannelNumTypeDef channel) { return DMAC->RawIntTCStatus    & (1 << channel); }
static inline bool DMAC_IsChannelRawIntErrorActive   (DMAC_ChannelNumTypeDef channel) { return DMAC->RawIntErrorStatus & (1 << channel); }

// If a peripheral is running on the same clock as the DMAC, synchronization logic for its requests can be disabled to
// improve response time. Peripheral request is between 0 and 15.
static inline void DMAC_EnableSyncRequest (uint32_t request) { DMAC->Sync &= ~(1 << request); }
static inline void DMAC_DisableSyncRequest(uint32_t request) { DMAC->Sync |=  (1 << request); }

static inline void DMAC_SetSrcAddress   (DMAC_ChannelNumTypeDef channel, uint32_t srcAddr) { DMAC->Channels[channel].SrcAddr       = srcAddr; }
static inline void DMAC_SetDstAddress   (DMAC_ChannelNumTypeDef channel, uint32_t dstAddr) { DMAC->Channels[channel].DstAddr       = dstAddr; }
static inline void DMAC_SetLLI          (DMAC_ChannelNumTypeDef channel, uint32_t lli)     { DMAC->Channels[channel].LLI           = lli;     }
static inline void DMAC_SetControl      (DMAC_ChannelNumTypeDef channel, uint32_t control) { DMAC->Channels[channel].Control       = control; }
static inline void DMAC_SetConfiguration(DMAC_ChannelNumTypeDef channel, uint32_t config)  { DMAC->Channels[channel].Configuration = config; }

static inline uint32_t DMAC_GetSrcAddress   (DMAC_ChannelNumTypeDef channel) { return DMAC->Channels[channel].SrcAddr;       }
static inline uint32_t DMAC_GetDstAddress   (DMAC_ChannelNumTypeDef channel) { return DMAC->Channels[channel].DstAddr;       }
static inline uint32_t DMAC_GetLLI          (DMAC_ChannelNumTypeDef channel) { return DMAC->Channels[channel].LLI;           }
static inline uint32_t DMAC_GetControl      (DMAC_ChannelNumTypeDef channel) { return DMAC->Channels[channel].Control;       }
static inline uint32_t DMAC_GetConfiguration(DMAC_ChannelNumTypeDef channel) { return DMAC->Channels[channel].Configuration; }

static inline uint32_t DMAC_GetTransferSize(DMAC_ChannelNumTypeDef channel) { return DMAC_GetControl(channel) & DMAC_MAX_TRANSFER_SIZE; }
static inline void     DMAC_SetTransferSize(DMAC_ChannelNumTypeDef channel, uint32_t transferSize)
{
  MODIFY_BIT(DMAC->Channels[channel].Control, DMAC_MAX_TRANSFER_SIZE, transferSize << DMAC_TRANSFER_SIZE_OFFSET);
}

static inline DMAC_FlowControlTypeDef DMAC_GetFlowControl(DMAC_ChannelNumTypeDef channel) { return (DMAC_FlowControlTypeDef)((DMAC->Channels[channel].Configuration >> DMAC_FLOW_CONTROL_OFFSET) & 0x7); }
static inline void DMAC_SetFlowControl(DMAC_ChannelNumTypeDef channel, DMAC_FlowControlTypeDef flow)
{
  MODIFY_BIT(DMAC->Channels[channel].Configuration, (0x7 << DMAC_FLOW_CONTROL_OFFSET), (flow << DMAC_FLOW_CONTROL_OFFSET));
}

#ifdef __cplusplus
}
#endif

#endif
