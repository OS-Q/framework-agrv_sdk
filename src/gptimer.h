#ifndef _AGM_GPTIMER_H
#define _AGM_GPTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

typedef struct
{
  __IO uint32_t CR1;   // 0x00, Control register 1
  __IO uint32_t CR2;   // 0x04, Control register 2
  __IO uint32_t SMCR;  // 0x08, Slave mode control register
  __IO uint32_t DIER;  // 0x0C, DMA/interrupt enable register
  __IO uint32_t SR;    // 0x10, Status register
  __IO uint32_t EGR;   // 0x14, Event generation register
  __IO uint32_t CCMR0; // 0x18, Capture/compare mode register 0
  __IO uint32_t CCMR1; // 0x1C, Capture/compare mode register 1
  __IO uint32_t CCER;  // 0x20, Capture/compare enable register
  __IO uint32_t CNT;   // 0x24, Counter
  __IO uint32_t PSC;   // 0x28, Prescaler
  __IO uint32_t ARR;   // 0x2C, Auto reload register
  __IO uint32_t RCR;   // 0x30, Repetition counter register
  __IO uint32_t CCR0;  // 0x34, Capture compare register 0
  __IO uint32_t CCR1;  // 0x38, Capture compare register 1
  __IO uint32_t CCR2;  // 0x3C, Capture compare register 2
  __IO uint32_t CCR3;  // 0x40, Capture compare register 3
  __IO uint32_t BDTR;  // 0x44, Break and dead time register
} GPTIMER_TypeDef;

#define GPTIMER_CR1_CMS_OFFSET 5
#define GPTIMER_CR1_CKD_OFFSET 8

#define GPTIMER_CR1_CEN  (1   << 0)                      // Counter enable
#define GPTIMER_CR1_UDIS (1   << 1)                      // Update disable
#define GPTIMER_CR1_URS  (1   << 2)                      // Update request source
#define GPTIMER_CR1_OPM  (1   << 3)                      // One pulse mode
#define GPTIMER_CR1_DIR  (1   << 4)                      // Direction
#define GPTIMER_CR1_CMS  (0x3 << GPTIMER_CR1_CMS_OFFSET) // Center-aligned mode selection
#define GPTIMER_CR1_ARPE (1   << 7)                      // Auto-reload preload enable
#define GPTIMER_CR1_CKD  (0x3 << GPTIMER_CR1_CKD_OFFSET) // Clock division

#define GPTIMER_CR2_MMS_OFFSET 4

#define GPTIMER_CR2_CCPC  (1   << 0)                      // Capture/Compare preloaded control
#define GPTIMER_CR2_CCUS  (1   << 2)                      // Capture/Compare control update selection
#define GPTIMER_CR2_CCDS  (1   << 3)                      // Capture/Compare DMA selection
#define GPTIMER_CR2_MMS   (0x7 << GPTIMER_CR2_MMS_OFFSET) // Master mode selection
#define GPTIMER_CR2_TI0S  (1   << 7)                      // TI0 selection
#define GPTIMER_CR2_OIS0  (1   << 8)                      // OC0  idle state
#define GPTIMER_CR2_OIS0N (1   << 9)                      // OC0N idle state
#define GPTIMER_CR2_OIS1  (1   << 10)                     // OC1  idle state
#define GPTIMER_CR2_OIS1N (1   << 11)                     // OC1N idle state
#define GPTIMER_CR2_OIS2  (1   << 12)                     // OC2  idle state
#define GPTIMER_CR2_OIS2N (1   << 13)                     // OC2N idle state
#define GPTIMER_CR2_OIS4  (1   << 14)                     // OC3  idle state
#define GPTIMER_CR2_OIS4N (1   << 15)                     // OC3N idle state

#define GPTIMER_SMCR_SMS_OFFSET  0
#define GPTIMER_SMCR_TS_OFFSET   4
#define GPTIMER_SMCR_ETF_OFFSET  8
#define GPTIMER_SMCR_ETPS_OFFSET 12

#define GPTIMER_SMCR_SMS  (0x7 << GPTIMER_SMCR_SMS_OFFSET)  // Slave mode selection
#define GPTIMER_SMCR_OCCS (1   << 3)                        // OCREF clear selection
#define GPTIMER_SMCR_TS   (0x7 << GPTIMER_SMCR_TS_OFFSET)   // Trigger selection
#define GPTIMER_SMCR_MSM  (1   << 7)                        // Master/slave mode
#define GPTIMER_SMCR_ETF  (0xf << GPTIMER_SMCR_ETF_OFFSET)  // External trigger filter
#define GPTIMER_SMCR_ETPS (0x3 << GPTIMER_SMCR_ETPS_OFFSET) // External trigger prescaler
#define GPTIMER_SMCR_ECE  (1   << 14)                       // External clock enable
#define GPTIMER_SMCR_ETP  (1   << 15)                       // External trigger polarity

#define GPTIMER_DIER_UIE   (1 << 0)  // Update interrupt enable
#define GPTIMER_DIER_CC0IE (1 << 1)  // Capture/Compare 0 interrupt enable
#define GPTIMER_DIER_CC1IE (1 << 2)  // Capture/Compare 1 interrupt enable
#define GPTIMER_DIER_CC2IE (1 << 3)  // Capture/Compare 2 interrupt enable
#define GPTIMER_DIER_CC3IE (1 << 4)  // Capture/Compare 3 interrupt enable
#define GPTIMER_DIER_COMIE (1 << 5)  // COM interrupt enable
#define GPTIMER_DIER_TIE   (1 << 6)  // Trigger interrupt enable
#define GPTIMER_DIER_BIE   (1 << 7)  // Break interrupt enable
#define GPTIMER_DIER_UDE   (1 << 8)  // Update DMA request enable
#define GPTIMER_DIER_CC0DE (1 << 9)  // Capture/Compare 0 DMA request enable
#define GPTIMER_DIER_CC1DE (1 << 10) // Capture/Compare 1 DMA request enable
#define GPTIMER_DIER_CC2DE (1 << 11) // Capture/Compare 2 DMA request enable
#define GPTIMER_DIER_CC3DE (1 << 12) // Capture/Compare 3 DMA request enable
#define GPTIMER_DIER_COMDE (1 << 13) // COM DMA request enable
#define GPTIMER_DIER_TDE   (1 << 14) // Trigger DMA request enable

#define GPTIMER_SR_UIF   (1 << 0)  // Update interrupt flag
#define GPTIMER_SR_CC0IF (1 << 1)  // Capture/Compare 0 interrupt flag
#define GPTIMER_SR_CC1IF (1 << 2)  // Capture/Compare 1 interrupt flag
#define GPTIMER_SR_CC2IF (1 << 3)  // Capture/Compare 2 interrupt flag
#define GPTIMER_SR_CC3IF (1 << 4)  // Capture/Compare 3 interrupt flag
#define GPTIMER_SR_COMIF (1 << 5)  // COM interrupt flag
#define GPTIMER_SR_TIF   (1 << 6)  // Trigger interrupt flag
#define GPTIMER_SR_BIF   (1 << 7)  // Break interrupt flag
#define GPTIMER_SR_CC0OF (1 << 9)  // Capture/Compare 0 overcapture flag
#define GPTIMER_SR_CC1OF (1 << 10) // Capture/Compare 1 overcapture flag
#define GPTIMER_SR_CC2OF (1 << 11) // Capture/Compare 2 overcapture flag
#define GPTIMER_SR_CC3OF (1 << 12) // Capture/Compare 3 overcapture flag

#define GPTIMER_EGR_UG   (1 << 0) // Update generation
#define GPTIMER_EGR_CC0G (1 << 1) // Capture/Compare 0 generation
#define GPTIMER_EGR_CC1G (1 << 2) // Capture/Compare 1 generation
#define GPTIMER_EGR_CC2G (1 << 3) // Capture/Compare 2 generation
#define GPTIMER_EGR_CC3G (1 << 4) // Capture/Compare 3 generation
#define GPTIMER_EGR_COMG (1 << 5) // Capture/Compare control update generation
#define GPTIMER_EGR_TG   (1 << 6) // Trigger generation
#define GPTIMER_EGR_BG   (1 << 7) // Break generation

#define GPTIMER_CCMR_CC0S_OFFSET   0
#define GPTIMER_CCMR_OC0M_OFFSET   4
#define GPTIMER_CCMR_IC0PSC_OFFSET 2
#define GPTIMER_CCMR_IC0F_OFFSET   4

#define GPTIMER_CCMR0_CC0S   (0x3 << 0)  // Capture/Compare 0 selection
#define GPTIMER_CCMR0_OC0FE  (1   << 2)  // Output compare 0 fast enable
#define GPTIMER_CCMR0_OC0PE  (1   << 3)  // Output compare 0 preload enable
#define GPTIMER_CCMR0_OC0M   (0x7 << 4)  // Output compare 0 mode
#define GPTIMER_CCMR0_OC0CE  (1   << 7)  // Output compare 0 clear enable
#define GPTIMER_CCMR0_CC1S   (0x3 << 8)  // Capture/Compare 1 selection
#define GPTIMER_CCMR0_OC1FE  (1   << 10) // Output compare 1 fast enable
#define GPTIMER_CCMR0_OC1PE  (1   << 11) // Output compare 1 preload enable
#define GPTIMER_CCMR0_OC1M   (0x7 << 12) // Output compare 1 mode
#define GPTIMER_CCMR0_OC1CE  (1   << 15) // Output compare 1 clear enable
#define GPTIMER_CCMR0_IC0PSC (0x3 << 2)  // Input capture 0 prescaler
#define GPTIMER_CCMR0_IC0F   (0xf << 4)  // Input capture 0 filter
#define GPTIMER_CCMR0_IC1PSC (0x3 << 10) // Input capture 1 prescaler
#define GPTIMER_CCMR0_IC1F   (0xf << 12) // Input capture 1 filter

#define GPTIMER_CCMR1_CC2S   (0x3 << 0)  // Capture/Compare 2 selection
#define GPTIMER_CCMR1_OC2FE  (1   << 2)  // Output compare 2 fast enable
#define GPTIMER_CCMR1_OC2PE  (1   << 3)  // Output compare 2 preload enable
#define GPTIMER_CCMR1_OC2M   (0x7 << 4)  // Output compare 2 mode
#define GPTIMER_CCMR1_OC2CE  (1   << 7)  // Output compare 2 clear enable
#define GPTIMER_CCMR1_CC3S   (0x3 << 8)  // Capture/Compare 3 selection
#define GPTIMER_CCMR1_OC3FE  (1   << 10) // Output compare 3 fast enable
#define GPTIMER_CCMR1_OC3PE  (1   << 11) // Output compare 3 preload enable
#define GPTIMER_CCMR1_OC3M   (0x7 << 12) // Output compare 3 mode
#define GPTIMER_CCMR1_OC3CE  (1   << 15) // Output compare 3 clear enable
#define GPTIMER_CCMR1_IC2PSC (0x3 << 2)  // Input capture 2 prescaler
#define GPTIMER_CCMR1_IC2F   (0xf << 4)  // Input capture 2 filter
#define GPTIMER_CCMR1_IC3PSC (0x3 << 10) // Input capture 3 prescaler
#define GPTIMER_CCMR1_IC3F   (0xf << 12) // Input capture 3 filter

#define GPTIMER_CCER_CC0E  (1 << 0)  // Capture/Compare 0 output enable
#define GPTIMER_CCER_CC0P  (1 << 1)  // Capture/Compare 0 output polarity
#define GPTIMER_CCER_CC0NE (1 << 2)  // Capture/Compare 0 complementary output enable
#define GPTIMER_CCER_CC0NP (1 << 3)  // Capture/Compare 0 complementary output polarity
#define GPTIMER_CCER_CC1E  (1 << 4)  // Capture/Compare 1 output enable
#define GPTIMER_CCER_CC1P  (1 << 5)  // Capture/Compare 1 output polarity
#define GPTIMER_CCER_CC1NE (1 << 6)  // Capture/Compare 1 complementary output enable
#define GPTIMER_CCER_CC1NP (1 << 7)  // Capture/Compare 1 complementary output polarity
#define GPTIMER_CCER_CC2E  (1 << 8)  // Capture/Compare 2 output enable
#define GPTIMER_CCER_CC2P  (1 << 9)  // Capture/Compare 2 output polarity
#define GPTIMER_CCER_CC2NE (1 << 10) // Capture/Compare 2 complementary output enable
#define GPTIMER_CCER_CC2NP (1 << 11) // Capture/Compare 2 complementary output polarity
#define GPTIMER_CCER_CC3E  (1 << 12) // Capture/Compare 3 output enable
#define GPTIMER_CCER_CC3P  (1 << 13) // Capture/Compare 3 output polarity
#define GPTIMER_CCER_CC3NE (1 << 14) // Capture/Compare 3 complementary output polarity
#define GPTIMER_CCER_CC3NP (1 << 15) // Capture/Compare 3 complementary output polarity

#define GPTIMER_BDTR_LOCK_OFFSET 8
#define GPTIMER_BDTR_BKF_OFFSET  16

#define GPTIMER_BDTR_DTG  (0xff << 0)  // Dead-Time generator setup
#define GPTIMER_BDTR_LOCK (0x3  << 8)  // Lock configuration
#define GPTIMER_BDTR_OSSI (1    << 10) // Off-State selection for idle mode
#define GPTIMER_BDTR_OSSR (1    << 11) // Off-State selection for run mode
#define GPTIMER_BDTR_BKE  (1    << 12) // Break enable
#define GPTIMER_BDTR_BKP  (1    << 13) // Break polarity
#define GPTIMER_BDTR_AOE  (1    << 14) // Automatic output enable
#define GPTIMER_BDTR_MOE  (1    << 15) // Main output enable
#define GPTIMER_BDTR_BKF  (0xf  << 16) // Break filter

typedef enum
{
  GPTIMER_UPDATESOURCE_REGULAR = 0,               // Update request from counter overflow/underflow, UG bit or update from the slave mode controller
  GPTIMER_UPDATESOURCE_COUNTER = GPTIMER_CR1_URS, // Update request from counter only
} GPTIMER_UpdateSourceTypeDef;

typedef enum
{
  GPTIMER_ONEPULSEMODE_REPETITIVE = 0,
  GPTIMER_ONEPULSEMODE_SINGLE     = GPTIMER_CR1_OPM,
} GPTIMER_OnePulseModeTypeDef;

typedef enum
{
  GPTIMER_COUNTERMODE_UP          = 0,
  GPTIMER_COUNTERMODE_DOWN        = GPTIMER_CR1_DIR,
  GPTIMER_COUNTERMODE_CENTER_DOWN = (0x1 << GPTIMER_CR1_CMS_OFFSET),
  GPTIMER_COUNTERMODE_CENTER_UP   = (0x2 << GPTIMER_CR1_CMS_OFFSET),
  GPTIMER_COUNTERMODE_CENTER_BOTH = (0x3 << GPTIMER_CR1_CMS_OFFSET),
} GPTIMER_CounterModeTypeDef;

typedef enum
{
  GPTIMER_CLOCKDIVISION_DIV1 = 0,
  GPTIMER_CLOCKDIVISION_DIV2 = (0x1 << GPTIMER_CR1_CKD_OFFSET),
  GPTIMER_CLOCKDIVISION_DIV4 = (0x2 << GPTIMER_CR1_CKD_OFFSET),
  GPTIMER_CLOCKDIVISION_DIV8 = (0x3 << GPTIMER_CR1_CKD_OFFSET),
} GPTIMER_ClockDivistionTypeDef;

typedef enum
{
  GPTIMER_COUNTERDIRECTION_UP   = 0,
  GPTIMER_COUNTERDIRECTION_DOWN = GPTIMER_CR1_DIR,
} GPTIMER_CounterDirectionTypeDef;

typedef enum
{
  GPTIMER_CCUPDATESOURCE_COMG_ONLY     = 0,
  GPTIMER_CCUPDATESOURCE_COMG_AND_TRGI = GPTIMER_CR2_CCUS,
} GPTIMER_CC_UpdateSourceTypeDef;

typedef enum
{
  GPTIMER_CCDMAREQUEST_CC     = 0,
  GPTIMER_CCDMAREQUEST_UPDATE = GPTIMER_CR2_CCDS,
} GPTIMER_CC_DmaRequestTypeDef;


typedef enum
{
  GPTIMER_TRGO_RESET  = 0,
  GPTIMER_TRGO_ENABLE = (0x1 << GPTIMER_CR2_MMS_OFFSET),
  GPTIMER_TRGO_UPDATE = (0x2 << GPTIMER_CR2_MMS_OFFSET),
  GPTIMER_TRGO_CC0IF  = (0x3 << GPTIMER_CR2_MMS_OFFSET),
  GPTIMER_TRGO_OC0REF = (0x4 << GPTIMER_CR2_MMS_OFFSET),
  GPTIMER_TRGO_OC1REF = (0x5 << GPTIMER_CR2_MMS_OFFSET),
  GPTIMER_TRGO_OC2REF = (0x6 << GPTIMER_CR2_MMS_OFFSET),
  GPTIMER_TRGO_OC3REF = (0x7 << GPTIMER_CR2_MMS_OFFSET),
} GPTIMER_TriggerOutputTypeDef;

typedef enum
{
  GPTIMER_CLOCKSOURCE_INTERNAL   = 0,
  GPTIMER_CLOCKSOURCE_EXT_MODE1  = (0x7 << GPTIMER_SMCR_SMS_OFFSET),
  GPTIMER_CLOCKSOURCE_EXT_MODE2  = GPTIMER_SMCR_ECE,
} GPTIMER_ClockSourceTypeDef;

typedef enum
{
  GPTIMER_ENCODERMODE_X2_TI0  = (0x1 << GPTIMER_SMCR_SMS_OFFSET),
  GPTIMER_ENCODERMODE_X2_TI1  = (0x2 << GPTIMER_SMCR_SMS_OFFSET),
  GPTIMER_ENCODERMODE_X4_TI01 = (0x3 << GPTIMER_SMCR_SMS_OFFSET),
} GPTIMER_EncodeModeTypeDef;

typedef enum
{
  GPTIMER_SLAVEMODE_DISABLED = 0,
  GPTIMER_SLAVEMODE_RESET    = (0x4 << GPTIMER_SMCR_SMS_OFFSET),
  GPTIMER_SLAVEMODE_GATED    = (0x5 << GPTIMER_SMCR_SMS_OFFSET),
  GPTIMER_SLAVEMODE_TRIGGER  = (0x6 << GPTIMER_SMCR_SMS_OFFSET),
} GPTIMER_SlaveModeTypeDef;

typedef enum
{
  GPTIMER_OCREF_CLR_INT_OCREF_CLR = 0,
  GPTIMER_OCREF_CLR_INT_ETR       = GPTIMER_SMCR_OCCS,
} GPTIMER_OCRefClearSourceTypeDef;

typedef enum
{
  GPTIMER_TS_ITR0    = 0,
  GPTIMER_TS_ITR1    = (0x1 << GPTIMER_SMCR_TS_OFFSET),
  GPTIMER_TS_ITR2    = (0x2 << GPTIMER_SMCR_TS_OFFSET),
  GPTIMER_TS_ITR3    = (0x3 << GPTIMER_SMCR_TS_OFFSET),
  GPTIMER_TS_TI0F_ED = (0x4 << GPTIMER_SMCR_TS_OFFSET),
  GPTIMER_TS_TI0FP0  = (0x5 << GPTIMER_SMCR_TS_OFFSET),
  GPTIMER_TS_TI1FP1  = (0x6 << GPTIMER_SMCR_TS_OFFSET),
  GPTIMER_TS_ETRF    = (0x7 << GPTIMER_SMCR_TS_OFFSET),
} GPTIMER_TriggerInputTypeDef;

typedef enum
{
  GPTIMER_ETR_FILTER_FDIV1      = 0,
  GPTIMER_ETR_FILTER_FDIV1_N2   = (0x1 << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV1_N4   = (0x2 << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV1_N8   = (0x3 << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV2_N6   = (0x4 << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV2_N8   = (0x5 << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV4_N6   = (0x6 << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV4_N8   = (0x7 << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV8_N6   = (0x8 << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV8_N8   = (0x9 << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV16_N5  = (0xa << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV16_N6  = (0xb << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV16_N8  = (0xc << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV32_N5  = (0xd << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV32_N6  = (0xe << GPTIMER_SMCR_ETF_OFFSET),
  GPTIMER_ETR_FILTER_FDIV32_N8  = (0xf << GPTIMER_SMCR_ETF_OFFSET),
} GPTIMER_ETR_FilterTypeDef;

typedef enum
{
  GPTIMER_ETR_PRESCALER_DIV1 = 0,
  GPTIMER_ETR_PRESCALER_DIV2 = (0x1 << GPTIMER_SMCR_ETPS_OFFSET),
  GPTIMER_ETR_PRESCALER_DIV4 = (0x2 << GPTIMER_SMCR_ETPS_OFFSET),
  GPTIMER_ETR_PRESCALER_DIV8 = (0x3 << GPTIMER_SMCR_ETPS_OFFSET),
} GPTIMER_ETR_PrescalerTypeDef;

typedef enum
{
  GPTIMER_ETR_POLARITY_NONINVERTED = 0,
  GPTIMER_ETR_POLARITY_INVERTED    = GPTIMER_SMCR_ETP,
} GPTIMER_ETR_PolarityTypeDef;

typedef enum
{
  GPTIMER_CHANNEL_CH0 = 0,
  GPTIMER_CHANNEL_CH1 = 1,
  GPTIMER_CHANNEL_CH2 = 2,
  GPTIMER_CHANNEL_CH3 = 3,
} GPTIMER_ChannelNumTypeDef;

typedef enum
{
  GPTIMER_ICMODE_DIRECTTI   = 0x1,
  GPTIMER_ICMODE_INDIRECTTI = 0x2,
  GPTIMER_ICMODE_TRC        = 0x3,
} GPTIMER_IC_ModeTypeDef;

typedef enum
{
  GPTIMER_OCSTATE_DISABLE = 0,
  GPTIMER_OCSTATE_ENABLE  = GPTIMER_CCER_CC0E,
} GPTIMER_OC_StateTypeDef;

typedef enum
{
  GPTIMER_OC_POLARITY_NONINVERTED = 0,
  GPTIMER_OC_POLARITY_INVERTED    = GPTIMER_CCER_CC0P,
} GPTIMER_OC_PolarityTypeDef;

typedef enum
{
  GPTIMER_OCIDLESTATE_LOW  = 0,
  GPTIMER_OCIDLESTATE_HIGH = GPTIMER_CR2_OIS0,
} GPTIMER_OC_IdleStateTypeDef;

typedef enum
{
  GPTIMER_OCMODE_FROZEN          = (0x0 << GPTIMER_CCMR_OC0M_OFFSET),
  GPTIMER_OCMODE_ACTIVE          = (0x1 << GPTIMER_CCMR_OC0M_OFFSET),
  GPTIMER_OCMODE_INACTIVE        = (0x2 << GPTIMER_CCMR_OC0M_OFFSET),
  GPTIMER_OCMODE_TOGGLE          = (0x3 << GPTIMER_CCMR_OC0M_OFFSET),
  GPTIMER_OCMODE_FORCED_INACTIVE = (0x4 << GPTIMER_CCMR_OC0M_OFFSET),
  GPTIMER_OCMODE_FORCED_ACTIVE   = (0x5 << GPTIMER_CCMR_OC0M_OFFSET),
  GPTIMER_OCMODE_PWM1            = (0x6 << GPTIMER_CCMR_OC0M_OFFSET), // Output channel x is active when CNT < CCRx (up counting) or CNT <= CCRx (down counting)
  GPTIMER_OCMODE_PWM2            = (0x7 << GPTIMER_CCMR_OC0M_OFFSET), // Output channel x is active when CNT >= CCRx (up counting) or CNT > CCRx (down counting)
} GPTIMER_OC_ModeTypeDef;

typedef enum
{
  GPTIMER_ICPSC_DIV1 = (0x0 << GPTIMER_CCMR_IC0PSC_OFFSET),
  GPTIMER_ICPSC_DIV2 = (0x1 << GPTIMER_CCMR_IC0PSC_OFFSET),
  GPTIMER_ICPSC_DIV4 = (0x2 << GPTIMER_CCMR_IC0PSC_OFFSET),
  GPTIMER_ICPSC_DIV8 = (0x3 << GPTIMER_CCMR_IC0PSC_OFFSET),
} GPTIMER_IC_PrescalerTypeDef;

typedef enum
{
  GPTIMER_IC_FILTER_FDIV1     = (0x0  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV1_N2  = (0x1  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV1_N4  = (0x2  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV1_N8  = (0x3  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV2_N6  = (0x4  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV2_N8  = (0x5  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV4_N6  = (0x6  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV4_N8  = (0x7  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV8_N6  = (0x8  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV8_N8  = (0x9  << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV16_N5 = (0x10 << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV16_N6 = (0x11 << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV16_N8 = (0x12 << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV32_N5 = (0x13 << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV32_N6 = (0x14 << GPTIMER_CCMR_IC0F_OFFSET),
  GPTIMER_IC_FILTER_FDIV32_N8 = (0x15 << GPTIMER_CCMR_IC0F_OFFSET),
} GPTIMER_IC_FilterTypeDef;

typedef enum
{
  GPTIMER_IC_POLARITY_RISING   = 0,
  GPTIMER_IC_POLARITY_FALLING  = GPTIMER_CCER_CC0P,
  GPTIMER_IC_POLARITY_BOTHEDGE = GPTIMER_CCER_CC0P | GPTIMER_CCER_CC0NP,
} GPTIMER_IC_PolarityTypeDef;

typedef enum
{
  GPTIMER_LOCKLEVEL_OFF = (0x0 << GPTIMER_BDTR_LOCK_OFFSET),
  GPTIMER_LOCKLEVEL_1   = (0x1 << GPTIMER_BDTR_LOCK_OFFSET),
  GPTIMER_LOCKLEVEL_2   = (0x2 << GPTIMER_BDTR_LOCK_OFFSET),
  GPTIMER_LOCKLEVEL_3   = (0x3 << GPTIMER_BDTR_LOCK_OFFSET),
} GPTIMER_LockLevelTypeDef;

typedef enum
{
  GPTIMER_BREAK_POLARITY_LOW  = 0,
  GPTIMER_BREAK_POLARITY_HIGH = GPTIMER_BDTR_BKP,
} GPTIMER_BreakPolarityTypeDef;

typedef enum
{
  GPTIMER_BREAK_FILTER_FDIV1     = (0x0 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV1_N2  = (0x1 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV1_N4  = (0x2 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV1_N8  = (0x3 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV2_N6  = (0x4 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV2_N8  = (0x5 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV4_N6  = (0x6 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV4_N8  = (0x7 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV8_N6  = (0x8 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV8_N8  = (0x9 << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV16_N5 = (0xa << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV16_N6 = (0xb << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV16_N8 = (0xc << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV32_N5 = (0xd << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV32_N6 = (0xe << GPTIMER_BDTR_BKF_OFFSET),
  GPTIMER_BREAK_FILTER_FDIV32_N8 = (0xf << GPTIMER_BDTR_BKF_OFFSET),
} GPTIMER_BreakFilterTypeDef;

typedef enum
{
  GPTIMER_OSSI_DISABLE = 0,
  GPTIMER_OSSI_ENABLE  = GPTIMER_BDTR_OSSI,
} GPTIMER_OffStateIdleTypeDef;

typedef enum
{
  GPTIMER_OSSR_DISABLE = 0,
  GPTIMER_OSSR_ENABLE  = GPTIMER_BDTR_OSSR,
} GPTIMER_OffStateRunTypeDef;

typedef enum
{
  GPTIMER_BREAK_DISABLE = 0,
  GPTIMER_BREAK_ENABLE  = GPTIMER_BDTR_BKE,
} GPTIMER_BreakStateTypeDef;

typedef enum
{
  GPTIMER_AUTOMATICOUTPUT_DISABLE = 0,
  GPTIMER_AUTOMATICOUTPUT_ENABLE  = GPTIMER_BDTR_AOE,
} GPTIMER_AutomaticOutputTypeDef;


static inline void GPTIMER_EnableCounter(GPTIMER_TypeDef  *gpt)   { gpt->CR1 |=  GPTIMER_CR1_CEN; }
static inline void GPTIMER_DisableCounter(GPTIMER_TypeDef *gpt)   { gpt->CR1 &= ~GPTIMER_CR1_CEN; }
static inline bool GPTIMER_IsEnabledCounter(GPTIMER_TypeDef *gpt) { return gpt->CR1 & GPTIMER_CR1_CEN; }

static inline void GPTIMER_EnableUpdateEvent(GPTIMER_TypeDef *gpt)    { gpt->CR1 |=  GPTIMER_CR1_UDIS; }
static inline void GPTIMER_DisableUpdateEvent(GPTIMER_TypeDef *gpt)   { gpt->CR1 &= ~GPTIMER_CR1_UDIS; }
static inline bool GPTIMER_IsEnabledUpdateEvent(GPTIMER_TypeDef *gpt) { return gpt->CR1 & GPTIMER_CR1_UDIS; }

static inline void GPTIMER_SetUpdateSource(GPTIMER_TypeDef *gpt, GPTIMER_UpdateSourceTypeDef update_source)
{
  MODIFY_REG(gpt->CR1, GPTIMER_CR1_URS, update_source);
}
static inline GPTIMER_UpdateSourceTypeDef GPTIMER_GetUpdateSource(GPTIMER_TypeDef *gpt)
{
  return (GPTIMER_UpdateSourceTypeDef)(gpt->CR1 & GPTIMER_CR1_URS);
}

static inline void GPTIMER_SetOnePulseMode(GPTIMER_TypeDef *gpt, GPTIMER_OnePulseModeTypeDef one_pulse_mode)
{
  MODIFY_REG(gpt->CR1, GPTIMER_CR1_OPM, one_pulse_mode);
}
static inline uint32_t GPTIMER_GetOnePulseMode(GPTIMER_TypeDef *gpt)
{
  return gpt->CR1 & GPTIMER_CR1_OPM;
}

static inline void GPTIMER_SetCounterMode(GPTIMER_TypeDef *gpt, GPTIMER_CounterModeTypeDef counter_mode)
{
  MODIFY_REG(gpt->CR1, GPTIMER_CR1_DIR | GPTIMER_CR1_CMS, counter_mode);
}

static inline GPTIMER_CounterModeTypeDef GPTIMER_GetCounterMode(GPTIMER_TypeDef *gpt)
{
  return (GPTIMER_CounterModeTypeDef)(gpt->CR1 & (GPTIMER_CR1_DIR | GPTIMER_CR1_CMS));
}

static inline void GPTIMER_EnableARRPreload(GPTIMER_TypeDef *gpt)    { gpt->CR1 |=  GPTIMER_CR1_ARPE; }
static inline void GPTIMER_DisableARRPreload(GPTIMER_TypeDef *gpt)   { gpt->CR1 &= ~GPTIMER_CR1_ARPE; }
static inline bool GPTIMER_IsEnabledARRPreload(GPTIMER_TypeDef *gpt) { return gpt->CR1 & GPTIMER_CR1_ARPE; }

static inline void GPTIMER_SetClockDivision(GPTIMER_TypeDef *gpt, GPTIMER_ClockDivistionTypeDef clock_division)
{
  MODIFY_REG(gpt->CR1, GPTIMER_CR1_CKD, clock_division);
}
static inline GPTIMER_ClockDivistionTypeDef GPTIMER_GetClockDivision(GPTIMER_TypeDef *gpt)
{
  return (GPTIMER_ClockDivistionTypeDef)(gpt->CR1 & GPTIMER_CR1_CKD);
}

static inline void GPTIMER_SetCounter(GPTIMER_TypeDef *gpt, uint32_t counter) { gpt->CNT = counter; }
static inline uint32_t GPTIMER_GetCounter(GPTIMER_TypeDef *gpt) { return gpt->CNT; }

static inline GPTIMER_CounterDirectionTypeDef GPTIMER_GetDirection(GPTIMER_TypeDef *gpt) { return (GPTIMER_CounterDirectionTypeDef)(gpt->CR1 & GPTIMER_CR1_DIR); }

static inline void GPTIMER_SetPrescaler(GPTIMER_TypeDef *gpt, uint32_t prescaler) { gpt->PSC = prescaler; }
static inline uint32_t GPTIMER_GetPrescaler(GPTIMER_TypeDef *gpt) { return gpt->PSC; }

static inline void GPTIMER_SetAutoReload(GPTIMER_TypeDef *gpt, uint32_t auto_reload) { gpt->ARR = auto_reload; }
static inline uint32_t GPTIMER_GetAutoReload(GPTIMER_TypeDef *gpt) { return gpt->ARR; }

static inline void GPTIMER_SetRepetitionCounter(GPTIMER_TypeDef *gpt, uint32_t repetition_counter) { gpt->RCR = repetition_counter; }
static inline uint32_t GPTIMER_GetRepetitionCounter(GPTIMER_TypeDef *gpt) { return gpt->RCR; }

static inline void GPTIMER_CC_EnablePreload(GPTIMER_TypeDef *gpt)  { gpt->CR2 |=  GPTIMER_CR2_CCPC; }
static inline void GPTIMER_CC_DisablePreload(GPTIMER_TypeDef *gpt) { gpt->CR2 &= ~GPTIMER_CR2_CCPC; }

static inline void GPTIMER_CC_SetUpdate(GPTIMER_TypeDef *gpt, GPTIMER_CC_UpdateSourceTypeDef update_source)
{
  MODIFY_REG(gpt->CR2, GPTIMER_CR2_CCUS, update_source);
}
static inline GPTIMER_CC_UpdateSourceTypeDef GPTIMER_CC_GetUpdate(GPTIMER_TypeDef *gpt)
{
  return (GPTIMER_CC_UpdateSourceTypeDef)(gpt->CR2 & GPTIMER_CR2_CCUS);
}

static inline void GPTIMER_CC_SetDMAReqTrigger(GPTIMER_TypeDef *gpt, GPTIMER_CC_DmaRequestTypeDef dma_reqeust)
{
  MODIFY_REG(gpt->CR2, GPTIMER_CR2_CCDS, dma_reqeust);
}
static inline GPTIMER_CC_DmaRequestTypeDef GPTIMER_CC_GetDMAReqTrigger(GPTIMER_TypeDef *gpt)
{
  return (GPTIMER_CC_DmaRequestTypeDef)(gpt->CR2 & GPTIMER_CR2_CCDS);
}

static inline void GPTIMER_SetTriggerOutput(GPTIMER_TypeDef *gpt, GPTIMER_TriggerOutputTypeDef trigger_output)
{
  MODIFY_REG(gpt->CR2, GPTIMER_CR2_MMS, trigger_output);
}
static inline GPTIMER_TriggerOutputTypeDef GPTIMER_GetTriggerOutput(GPTIMER_TypeDef *gpt)
{
  return (GPTIMER_TriggerOutputTypeDef)(gpt->CR2 & GPTIMER_CR2_MMS);
}

static inline void GPTIMER_IC_EnableXORCombination(GPTIMER_TypeDef *gpt)    { gpt->CR2 |=  GPTIMER_CR2_TI0S; }
static inline void GPTIMER_IC_DisableXORCombination(GPTIMER_TypeDef *gpt)   { gpt->CR2 &= ~GPTIMER_CR2_TI0S; }
static inline bool GPTIMER_IC_IsEnabledXORCombination(GPTIMER_TypeDef *gpt) { return gpt->CR2 & GPTIMER_CR2_TI0S; }

static inline void GPTIMER_EnableExternalClock(GPTIMER_TypeDef *gpt)  { gpt->SMCR |=  GPTIMER_SMCR_ECE; }
static inline void GPTIMER_DisableExternalClock(GPTIMER_TypeDef *gpt) { gpt->SMCR &= ~GPTIMER_SMCR_ECE; }
static inline bool GPTIMER_IsEnabledExternalClock(GPTIMER_TypeDef *gpt) { return gpt->SMCR & GPTIMER_SMCR_ECE; }

static inline void GPTIMER_SetClockSource(GPTIMER_TypeDef *gpt, GPTIMER_ClockSourceTypeDef clock_source)
{
  MODIFY_REG(gpt->SMCR, GPTIMER_SMCR_SMS | GPTIMER_SMCR_ECE, clock_source);
}
static inline void GPTIMER_SetEncoderMode(GPTIMER_TypeDef *gpt, GPTIMER_EncodeModeTypeDef encoder_mode)
{
  MODIFY_REG(gpt->SMCR, GPTIMER_SMCR_SMS, encoder_mode);
}
static inline void GPTIMER_SetSlaveMode(GPTIMER_TypeDef *gpt, GPTIMER_SlaveModeTypeDef slave_mode)
{
  MODIFY_REG(gpt->SMCR, GPTIMER_SMCR_SMS, slave_mode);
}

static inline void GPTIMER_SetOCRefClearInputSource(GPTIMER_TypeDef *gpt, GPTIMER_OCRefClearSourceTypeDef ocref_clear_source)
{
  MODIFY_REG(gpt->SMCR, GPTIMER_SMCR_OCCS, ocref_clear_source);
}

static inline void GPTIMER_SetTriggerInput(GPTIMER_TypeDef *gpt, GPTIMER_TriggerInputTypeDef trigger_input)
{
  MODIFY_REG(gpt->SMCR, GPTIMER_SMCR_TS, trigger_input);
}

static inline void GPTIMER_EnableMasterSlaveMode(GPTIMER_TypeDef *gpt)    { gpt->SMCR |=  GPTIMER_SMCR_MSM; }
static inline void GPTIMER_DisableMasterSlaveMode(GPTIMER_TypeDef *gpt)   { gpt->SMCR &= ~GPTIMER_SMCR_MSM; }
static inline bool GPTIMER_IsEnabledMasterSlaveMode(GPTIMER_TypeDef *gpt) { return gpt->SMCR & GPTIMER_SMCR_MSM; }

static inline void GPTIMER_ConfigETR(GPTIMER_TypeDef *gpt, GPTIMER_ETR_PolarityTypeDef polarity,
                              GPTIMER_ETR_PrescalerTypeDef prescaler, GPTIMER_ETR_FilterTypeDef filter)
{
  MODIFY_REG(gpt->SMCR, GPTIMER_SMCR_ETP | GPTIMER_SMCR_ETPS | GPTIMER_SMCR_ETF, polarity | prescaler | filter);
}

static inline void GPTIMER_EnableIntUpdate(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_UIE; }
static inline void GPTIMER_DisableIntUpdate(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_UIE; }
static inline bool GPTIMER_IsEnabledIntUpdate(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_UIE; }

static inline void GPTIMER_EnableIntCC0(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_CC0IE; }
static inline void GPTIMER_DisableIntCC0(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_CC0IE; }
static inline bool GPTIMER_IsEnabledIntCC0(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_CC0IE; }

static inline void GPTIMER_EnableIntCC1(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_CC1IE; }
static inline void GPTIMER_DisableIntCC1(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_CC1IE; }
static inline bool GPTIMER_IsEnabledIntCC1(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_CC1IE; }

static inline void GPTIMER_EnableIntCC2(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_CC2IE; }
static inline void GPTIMER_DisableIntCC2(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_CC2IE; }
static inline bool GPTIMER_IsEnabledIntCC2(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_CC2IE; }

static inline void GPTIMER_EnableIntCC3(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_CC3IE; }
static inline void GPTIMER_DisableIntCC3(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_CC3IE; }
static inline bool GPTIMER_IsEnabledIntCC3(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_CC3IE; }

static inline void GPTIMER_EnableIntCom(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_COMIE; }
static inline void GPTIMER_DisableIntCom(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_COMIE; }
static inline bool GPTIMER_IsEnabledIntCom(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_COMIE; }

static inline void GPTIMER_EnableIntTrigger(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_TIE; }
static inline void GPTIMER_DisableIntTrigger(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_TIE; }
static inline bool GPTIMER_IsEnabledIntTrigger(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_TIE; }

static inline void GPTIMER_EnableIntBreak(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_BIE; }
static inline void GPTIMER_DisableIntBreak(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_BIE; }
static inline bool GPTIMER_IsEnabledIntBreak(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_BIE; }

static inline void GPTIMER_EnableDmaUpdate(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_UDE; }
static inline void GPTIMER_DisableDmaUpdate(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_UDE; }
static inline bool GPTIMER_IsEnabledDmaUpdate(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_UDE; }

static inline void GPTIMER_EnableDmaCC0(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_CC0DE; }
static inline void GPTIMER_DisableDmaCC0(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_CC0DE; }
static inline bool GPTIMER_IsEnabledDmaCC0(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_CC0DE; }

static inline void GPTIMER_EnableDmaCC1(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_CC1DE; }
static inline void GPTIMER_DisableDmaCC1(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_CC1DE; }
static inline bool GPTIMER_IsEnabledDmaCC1(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_CC1DE; }

static inline void GPTIMER_EnableDmaCC2(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_CC2DE; }
static inline void GPTIMER_DisableDmaCC2(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_CC2DE; }
static inline bool GPTIMER_IsEnabledDmaCC2(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_CC2DE; }

static inline void GPTIMER_EnableDmaCC3(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_CC3DE; }
static inline void GPTIMER_DisableDmaCC3(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_CC3DE; }
static inline bool GPTIMER_IsEnabledDmaCC3(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_CC3DE; }

static inline void GPTIMER_EnableDmaCom(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_COMDE; }
static inline void GPTIMER_DisableDmaCom(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_COMDE; }
static inline bool GPTIMER_IsEnabledDmaCom(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_COMDE; }

static inline void GPTIMER_EnableDmaTrigger(GPTIMER_TypeDef *gpt)    { gpt->DIER |=  GPTIMER_DIER_TDE; }
static inline void GPTIMER_DisableDmaTrigger(GPTIMER_TypeDef *gpt)   { gpt->DIER &= ~GPTIMER_DIER_TDE; }
static inline bool GPTIMER_IsEnabledDmaTrigger(GPTIMER_TypeDef *gpt) { return gpt->DIER & GPTIMER_DIER_TDE; }

static inline void GPTIMER_ClearFlagUpdate(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_UIF; }
static inline bool GPTIMER_IsActiveFlagUpdate(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_UIF; }

static inline void GPTIMER_ClearFlagCC0(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_CC0IF; }
static inline bool GPTIMER_IsActiveFlagCC0(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_CC0IF; }

static inline void GPTIMER_ClearFlagCC1(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_CC1IF; }
static inline bool GPTIMER_IsActiveFlagCC1(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_CC1IF; }

static inline void GPTIMER_ClearFlagCC2(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_CC2IF; }
static inline bool GPTIMER_IsActiveFlagCC2(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_CC2IF; }

static inline void GPTIMER_ClearFlagCC3(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_CC3IF; }
static inline bool GPTIMER_IsActiveFlagCC3(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_CC3IF; }

static inline void GPTIMER_ClearFlagCom(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_COMIF; }
static inline bool GPTIMER_IsActiveFlagCom(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_COMIF; }

static inline void GPTIMER_ClearFlagTrigger(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_TIF; }
static inline bool GPTIMER_IsActiveFlagTrigger(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_TIF; }

static inline void GPTIMER_ClearFlagBreak(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_BIF; }
static inline bool GPTIMER_IsActiveFlagBreak(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_BIF; }

static inline void GPTIMER_ClearFlagCC0Over(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_CC0OF; }
static inline bool GPTIMER_IsActiveFlagCC0Over(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_CC0OF; }

static inline void GPTIMER_ClearFlagCC1Over(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_CC1OF; }
static inline bool GPTIMER_IsActiveFlagCC1Over(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_CC1OF; }

static inline void GPTIMER_ClearFlagCC2Over(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_CC2OF; }
static inline bool GPTIMER_IsActiveFlagCC2Over(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_CC2OF; }

static inline void GPTIMER_ClearFlagCC3Over(GPTIMER_TypeDef *gpt)    { gpt->SR = ~GPTIMER_SR_CC3OF; }
static inline bool GPTIMER_IsActiveFlagCC3Over(GPTIMER_TypeDef *gpt) { return gpt->SR & GPTIMER_SR_CC3OF; }

static inline void GPTIMER_CLearAllFlags(GPTIMER_TypeDef *gpt) { gpt->SR = 0; }

static inline void GPTIMER_GenerateEventUpdate(GPTIMER_TypeDef *gpt)  { gpt->EGR = GPTIMER_EGR_UG; }
static inline void GPTIMER_GenerateEventCC0(GPTIMER_TypeDef *gpt)     { gpt->EGR = GPTIMER_EGR_CC0G; }
static inline void GPTIMER_GenerateEventCC1(GPTIMER_TypeDef *gpt)     { gpt->EGR = GPTIMER_EGR_CC1G; }
static inline void GPTIMER_GenerateEventCC2(GPTIMER_TypeDef *gpt)     { gpt->EGR = GPTIMER_EGR_CC2G; }
static inline void GPTIMER_GenerateEventCC3(GPTIMER_TypeDef *gpt)     { gpt->EGR = GPTIMER_EGR_CC3G; }
static inline void GPTIMER_GenerateEventCom(GPTIMER_TypeDef *gpt)     { gpt->EGR = GPTIMER_EGR_COMG; }
static inline void GPTIMER_GenerateEventTrigger(GPTIMER_TypeDef *gpt) { gpt->EGR = GPTIMER_EGR_TG; }
static inline void GPTIMER_GenerateEventBreak(GPTIMER_TypeDef *gpt)   { gpt->EGR = GPTIMER_EGR_BG; }

static inline uint32_t GPTIMER_GetDtsPeriod(uint32_t freq, GPTIMER_ClockDivistionTypeDef clkdiv)
{
  return 1000000000 / (freq >> (clkdiv >> GPTIMER_CR1_CKD_OFFSET)); // In ns
}

static inline uint8_t GPTIMER_CalculateDTG(uint32_t freq, GPTIMER_ClockDivistionTypeDef clkdiv, uint32_t dead_time)
{
  const int cycles = dead_time / GPTIMER_GetDtsPeriod(freq, clkdiv);
  if (cycles < 128) {
    return cycles;              // DTG[7:5] = 0xx
  } else if (cycles < 256) {
    return 64 + (cycles / 2);   // DTG[7:5] = 10x
  } else if (cycles < 512) {
    return 160 + (cycles / 8);  // DTG[7:5] = 110
  } else if (cycles < 1024) {
    return 192 + (cycles / 16); // DTG[7:5] = 111
  } else {
    return 255;
  }
}

static inline uint32_t GPTIMER_CalculateDeadTime(uint32_t freq, GPTIMER_ClockDivistionTypeDef clkdiv, uint8_t dtg)
{
  const int period = GPTIMER_GetDtsPeriod(freq, clkdiv);
  if (dtg >> 7 == 0b0) {
    return dtg * period;                      // DTG[7:5] = 0xx
  } else if (dtg >> 6 == 0b10) {
    return (64 + (dtg & 0x3f)) * period * 2;  // DTG[7:5] = 10x
  } else if (dtg >> 5 == 0b110) {
    return (32 + (dtg & 0x1f)) * period * 8;  // DTG[7:5] = 110
  } else {
    return (32 + (dtg & 0x1f)) * period * 16; // DTG[7:5] = 111
  }
}

#define GPTIMER_CCMRx(gpt, channel) (*(&(gpt->CCMR0) + (channel / 2)))
#define GPTIMER_CCRx(gpt, channel)  (*(&(gpt->CCR0) + channel))
#define GPTIMER_CCMR_SHIFT(channel) (channel % 2 * 8)
#define GPTIMER_CCER_SHIFT(channel) (channel * 4)
#define GPTIMER_CR2_SHIFT(channel)  (channel * 2)

static inline void GPTIMER_CC_EnableChannel(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)   { gpt->CCER |=  (GPTIMER_CCER_CC0E << GPTIMER_CCER_SHIFT(channel)); }
static inline void GPTIMER_CC_DisableChannel(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)  { gpt->CCER &= ~(GPTIMER_CCER_CC0E << GPTIMER_CCER_SHIFT(channel)); }

static inline bool GPTIMER_CC_IsEnabledChannel(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)  { return gpt->CCER & (GPTIMER_CCER_CC0E  << GPTIMER_CCER_SHIFT(channel)); }
static inline bool GPTIMER_OCN_IsEnabledChannel(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel) { return gpt->CCER & (GPTIMER_CCER_CC0NE << GPTIMER_CCER_SHIFT(channel)); }

static inline void GPTIMER_OC_SetEnableState(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel,
                                      GPTIMER_OC_StateTypeDef oc_state, GPTIMER_OC_StateTypeDef ocn_state)
{
  MODIFY_REG(gpt->CCER, (GPTIMER_CCER_CC0E | GPTIMER_CCER_CC0NE) << GPTIMER_CCER_SHIFT(channel), (oc_state | (ocn_state << 2)) << GPTIMER_CCER_SHIFT(channel));
}

static inline void GPTIMER_OC_SetMode(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_OC_ModeTypeDef oc_mode)
{
  int ccmr_shift = GPTIMER_CCMR_SHIFT(channel);
  MODIFY_REG(GPTIMER_CCMRx(gpt, channel), (GPTIMER_CCMR0_OC0M | GPTIMER_CCMR0_CC0S) << ccmr_shift, oc_mode << ccmr_shift);
}

static inline GPTIMER_OC_ModeTypeDef GPTIMER_OC_GetMode(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  int ccmr_shift = GPTIMER_CCMR_SHIFT(channel);
  return (GPTIMER_OC_ModeTypeDef)((GPTIMER_CCMRx(gpt, channel) & (GPTIMER_CCMR0_OC0M << ccmr_shift)) >> ccmr_shift);
}

static inline void GPTIMER_OC_EnableFast(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  GPTIMER_CCMRx(gpt, channel) |= (GPTIMER_CCMR0_OC0FE << GPTIMER_CCMR_SHIFT(channel));
}

static inline void GPTIMER_OC_DisableFast(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  GPTIMER_CCMRx(gpt, channel) &= ~(GPTIMER_CCMR0_OC0FE << GPTIMER_CCMR_SHIFT(channel));
}

static inline bool GPTIMER_OC_IsEnabledFast(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  return GPTIMER_CCMRx(gpt, channel) & (GPTIMER_CCMR0_OC0FE << GPTIMER_CCMR_SHIFT(channel));
}

static inline void GPTIMER_OC_EnablePreload(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  GPTIMER_CCMRx(gpt, channel) |= (GPTIMER_CCMR0_OC0PE << GPTIMER_CCMR_SHIFT(channel));
}

static inline void GPTIMER_OC_DisablePreload(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  GPTIMER_CCMRx(gpt, channel) &= ~(GPTIMER_CCMR0_OC0PE << GPTIMER_CCMR_SHIFT(channel));
}

static inline bool GPTIMER_OC_IsEnabledPreload(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  return GPTIMER_CCMRx(gpt, channel) & (GPTIMER_CCMR0_OC0PE << GPTIMER_CCMR_SHIFT(channel));
}

static inline void GPTIMER_OC_EnableClear(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  GPTIMER_CCMRx(gpt, channel) |= (GPTIMER_CCMR0_OC0CE << GPTIMER_CCMR_SHIFT(channel));
}


static inline void GPTIMER_OC_DisableClear(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  GPTIMER_CCMRx(gpt, channel) &= ~(GPTIMER_CCMR0_OC0CE << GPTIMER_CCMR_SHIFT(channel));
}

static inline bool GPTIMER_OC_IsEnabledClear(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  return GPTIMER_CCMRx(gpt, channel) & (GPTIMER_CCMR0_OC0CE << GPTIMER_CCMR_SHIFT(channel));
}

static inline void GPTIMER_OC_SetPolarity(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_OC_PolarityTypeDef oc_polarity)
{
  int ccer_shift = GPTIMER_CCER_SHIFT(channel);
  MODIFY_REG(gpt->CCER, GPTIMER_CCER_CC0P << ccer_shift, oc_polarity << ccer_shift);
}

static inline GPTIMER_OC_PolarityTypeDef GPTIMER_OC_GetPolarity(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  int ccer_shift = GPTIMER_CCER_SHIFT(channel);
  return (GPTIMER_OC_PolarityTypeDef)((gpt->CCER & (GPTIMER_CCER_CC0P << ccer_shift)) >> ccer_shift);
}

static inline void GPTIMER_OC_SetIdleState(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_OC_IdleStateTypeDef oc_idlestate)
{
  int cr2_shift = GPTIMER_CR2_SHIFT(channel);
  MODIFY_REG(gpt->CR2, GPTIMER_CR2_OIS0 << cr2_shift, oc_idlestate << cr2_shift);
}

static inline GPTIMER_OC_IdleStateTypeDef GPTIMER_OC_GetIdleState(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  int cr2_shift = GPTIMER_CR2_SHIFT(channel);
  return (GPTIMER_OC_IdleStateTypeDef)((gpt->CR2 & (GPTIMER_CR2_OIS0 << cr2_shift)) >> cr2_shift);
}

static inline void GPTIMER_OCN_SetPolarity(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_OC_PolarityTypeDef oc_polarity)
{
  int ccer_shift = GPTIMER_CCER_SHIFT(channel);
  MODIFY_REG(gpt->CCER, GPTIMER_CCER_CC0NP << ccer_shift, oc_polarity << 2 << ccer_shift);
}

static inline GPTIMER_OC_PolarityTypeDef GPTIMER_OCN_GetPolarity(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  int ccer_shift = GPTIMER_CCER_SHIFT(channel);
  return (GPTIMER_OC_PolarityTypeDef)((gpt->CCER & (GPTIMER_CCER_CC0NP << ccer_shift)) >> ccer_shift);
}

static inline void GPTIMER_OCN_SetIdleState(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_OC_IdleStateTypeDef oc_idlestate)
{
  int cr2_shift = GPTIMER_CR2_SHIFT(channel);
  MODIFY_REG(gpt->CR2, GPTIMER_CR2_OIS0N << cr2_shift, oc_idlestate << 1 << cr2_shift);
}

static inline GPTIMER_OC_IdleStateTypeDef GPTIMER_OCN_GetIdleState(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  int cr2_shift = GPTIMER_CR2_SHIFT(channel);
  return (GPTIMER_OC_IdleStateTypeDef)((gpt->CR2 & (GPTIMER_CR2_OIS0N << cr2_shift)) >> cr2_shift);
}

static inline void GPTIMER_OC_SetCompare(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, uint32_t compare_value)
{
  GPTIMER_CCRx(gpt, channel) = compare_value;
}

static inline uint32_t GPTIMER_OC_GetCompare(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  return GPTIMER_CCRx(gpt, channel);
}

static inline void GPTIMER_SetDeadTimeGenerator(GPTIMER_TypeDef *gpt, uint8_t dtg)
{
  MODIFY_REG(gpt->BDTR, GPTIMER_BDTR_DTG, dtg);
}

static inline uint8_t GPTIMER_GetDeadTimeGenerator(GPTIMER_TypeDef *gpt)
{
  return gpt->BDTR & GPTIMER_BDTR_DTG;
}

static inline void GPTIMER_IC_SetInputMode(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_IC_ModeTypeDef ic_mode)
{
  int ccmr_shift = GPTIMER_CCMR_SHIFT(channel);
  MODIFY_REG(GPTIMER_CCMRx(gpt, channel), GPTIMER_CCMR0_CC0S << ccmr_shift, ic_mode << ccmr_shift);
}

static inline GPTIMER_IC_ModeTypeDef GPTIMER_IC_GetInputMode(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  int ccmr_shift = GPTIMER_CCMR_SHIFT(channel);
  return (GPTIMER_IC_ModeTypeDef)((GPTIMER_CCMRx(gpt, channel) & (GPTIMER_CCMR0_CC0S << ccmr_shift)) >> ccmr_shift);
}


static inline void GPTIMER_IC_SetPrescaler(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_IC_PrescalerTypeDef ic_prescaler)
{
  int ccmr_shift = GPTIMER_CCMR_SHIFT(channel);
  MODIFY_REG(GPTIMER_CCMRx(gpt, channel), GPTIMER_CCMR0_IC0PSC << ccmr_shift, ic_prescaler << ccmr_shift);
}

static inline GPTIMER_IC_PrescalerTypeDef GPTIMER_IC_GetPrescaler(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  int ccmr_shift = GPTIMER_CCMR_SHIFT(channel);
  return (GPTIMER_IC_PrescalerTypeDef)((GPTIMER_CCMRx(gpt, channel) & (GPTIMER_CCMR0_IC0PSC << ccmr_shift)) >> ccmr_shift);
}

static inline void GPTIMER_IC_SetFilter(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_IC_FilterTypeDef ic_filter)
{
  int ccmr_shift = GPTIMER_CCMR_SHIFT(channel);
  MODIFY_REG(GPTIMER_CCMRx(gpt, channel), GPTIMER_CCMR0_IC0F << ccmr_shift, ic_filter << ccmr_shift);
}

static inline GPTIMER_IC_FilterTypeDef GPTIMER_IC_GetFilter(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  int ccmr_shift = GPTIMER_CCMR_SHIFT(channel);
  return (GPTIMER_IC_FilterTypeDef)((GPTIMER_CCMRx(gpt, channel) & (GPTIMER_CCMR0_IC0F << ccmr_shift)) >> ccmr_shift);
}

static inline void GPTIMER_IC_SetPolarity(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_IC_PolarityTypeDef ic_polarity)
{
  int ccer_shift = GPTIMER_CCER_SHIFT(channel);
  MODIFY_REG(gpt->CCER, (GPTIMER_CCER_CC0P | GPTIMER_CCER_CC0NP) << ccer_shift, ic_polarity << ccer_shift);
}

static inline GPTIMER_IC_PolarityTypeDef GPTIMER_IC_GetPolarity(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  int ccer_shift = GPTIMER_CCER_SHIFT(channel);
  return (GPTIMER_IC_PolarityTypeDef)((gpt->CCER & ((GPTIMER_CCER_CC0P | GPTIMER_CCER_CC0NP) << ccer_shift)) >> ccer_shift);
}

static inline uint32_t GPTIMER_IC_GetCapture(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel)
{
  return GPTIMER_CCRx(gpt, channel);
}

static inline void GPTIMER_SetOffStateIdle(GPTIMER_TypeDef *gpt, GPTIMER_OffStateIdleTypeDef state)
{
  MODIFY_REG(gpt->BDTR, GPTIMER_BDTR_OSSI, state);
}

static inline void GPTIMER_SetOffStateRun(GPTIMER_TypeDef *gpt, GPTIMER_OffStateRunTypeDef state)
{
  MODIFY_REG(gpt->BDTR, GPTIMER_BDTR_OSSR, state);
}

static inline void GPTIMER_SetBreakState(GPTIMER_TypeDef *gpt, GPTIMER_BreakStateTypeDef state)
{
  MODIFY_REG(gpt->BDTR, GPTIMER_BDTR_BKE, state);
}

static inline void GPTIMER_ConfigBreak(GPTIMER_TypeDef *gpt, GPTIMER_BreakPolarityTypeDef break_polarity, GPTIMER_BreakFilterTypeDef break_filter)
{
  MODIFY_REG(gpt->BDTR, GPTIMER_BDTR_BKP | GPTIMER_BDTR_BKF, break_polarity | break_filter);
}

static inline void GPTIMER_SetAutomaticOutput(GPTIMER_TypeDef *gpt, GPTIMER_AutomaticOutputTypeDef state)
{
  MODIFY_REG(gpt->BDTR, GPTIMER_BDTR_AOE, state);
}
static inline bool GPTIMER_IsEnabledAutomaticOutput(GPTIMER_TypeDef *gpt) { return gpt->BDTR & GPTIMER_BDTR_AOE; }

static inline void GPTIMER_EnableAllOutputs(GPTIMER_TypeDef *gpt)    { gpt->BDTR |=  GPTIMER_BDTR_MOE; }
static inline void GPTIMER_DisableAllOutputs(GPTIMER_TypeDef *gpt)   { gpt->BDTR &= ~GPTIMER_BDTR_MOE; }
static inline bool GPTIMER_IsEnabledAllOutputs(GPTIMER_TypeDef *gpt) { return gpt->BDTR & GPTIMER_BDTR_MOE; }


typedef struct
{
  GPTIMER_CounterModeTypeDef    CounterMode;
  GPTIMER_ClockDivistionTypeDef ClockDivision;
  uint16_t                      Prescaler;
  uint16_t                      RepetitionCounter;
  uint32_t                      Autoreload;
} GPTIMER_InitTypeDef;

typedef struct
{
  GPTIMER_OC_ModeTypeDef      OCMode;
  GPTIMER_OC_StateTypeDef     OCState;
  GPTIMER_OC_StateTypeDef     OCNState;
  GPTIMER_OC_PolarityTypeDef  OCPolarity;
  GPTIMER_OC_PolarityTypeDef  OCNPolarity;
  GPTIMER_OC_IdleStateTypeDef OCIdleState;
  GPTIMER_OC_IdleStateTypeDef OCNIdleState;
  uint32_t                    CompareValue;
} GPTIMER_OC_InitTypeDef;

typedef struct
{
  GPTIMER_IC_PolarityTypeDef  ICPolarity;
  GPTIMER_IC_ModeTypeDef      ICMode;
  GPTIMER_IC_PrescalerTypeDef ICPrescaler;
  GPTIMER_IC_FilterTypeDef    ICFilter;
} GPTIMER_IC_InitTypeDef;

typedef struct
{
  GPTIMER_EncodeModeTypeDef   EncoderMode;
  GPTIMER_IC_PolarityTypeDef  IC0Polarity;
  GPTIMER_IC_ModeTypeDef      IC0Mode;
  GPTIMER_IC_PrescalerTypeDef IC0Prescaler;
  GPTIMER_IC_FilterTypeDef    IC0Filter;
  GPTIMER_IC_PolarityTypeDef  IC1Polarity;
  GPTIMER_IC_ModeTypeDef      IC1Mode;
  GPTIMER_IC_PrescalerTypeDef IC1Prescaler;
  GPTIMER_IC_FilterTypeDef    IC1Filter;
} GPTIMER_ENCODER_InitTypeDef;

typedef struct
{
  GPTIMER_IC_PolarityTypeDef  IC0Polarity;
  GPTIMER_IC_PrescalerTypeDef IC0Prescaler;
  GPTIMER_IC_FilterTypeDef    IC0Filter;
  uint32_t                    CommutationDelay;
} GPTIMER_HALLSENSOR_InitTypeDef;

typedef struct
{
  GPTIMER_OffStateIdleTypeDef    OSSIState;
  GPTIMER_OffStateRunTypeDef     OSSRState;
  GPTIMER_LockLevelTypeDef       LockLevel;
  GPTIMER_BreakStateTypeDef      BreakState;
  GPTIMER_BreakPolarityTypeDef   BreakPolarity;
  GPTIMER_BreakFilterTypeDef     BreakFilter;
  GPTIMER_AutomaticOutputTypeDef AutomaticOutput;
  uint8_t                        DeadTimeGenerator;
} GPTIMER_BDTR_InitTypeDef;


void GPTIMER_StructInit(GPTIMER_InitTypeDef *GPTIMER_InitStruct);
ReturnCodeTypedef GPTIMER_Init(GPTIMER_TypeDef *gpt, GPTIMER_InitTypeDef *GPTIMER_InitStruct);

void GPTIMER_OC_StructInit(GPTIMER_OC_InitTypeDef *oc_init);
void GPTIMER_OC_Init(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_OC_InitTypeDef *oc_init);

void GPTIMER_IC_StructInit(GPTIMER_IC_InitTypeDef *ic_init);
void GPTIMER_IC_Init(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_IC_InitTypeDef *ic_init);

void GPTIMER_ENCODER_StructInit(GPTIMER_ENCODER_InitTypeDef *encoder_init);
ReturnCodeTypedef GPTIMER_ENCODER_Init(GPTIMER_TypeDef *gpt, GPTIMER_ENCODER_InitTypeDef *encoder_init);

void GPTIMER_HALLSENSOR_StructInit(GPTIMER_HALLSENSOR_InitTypeDef *hall_init);
ReturnCodeTypedef GPTIMER_HALLSENSOR_Init(GPTIMER_TypeDef *gpt, GPTIMER_HALLSENSOR_InitTypeDef *hall_init);

void GPTIMER_BDTR_StructInit(GPTIMER_BDTR_InitTypeDef *bdtr_init);
ReturnCodeTypedef GPTIMER_BDTR_Init(GPTIMER_TypeDef *gpt, GPTIMER_BDTR_InitTypeDef *bdtr_init);

#ifdef __cplusplus
}
#endif

#endif
