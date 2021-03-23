#ifndef _AGM_RTC_H
#define _AGM_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

#define RTC_FLAG_SEC   (1 << 0) // Second flag
#define RTC_FLAG_ALR   (1 << 1) // Alarm flag
#define RTC_FLAG_OW    (1 << 2) // Overflow flag
#define RTC_FLAG_RSF   (1 << 3) // Registers Synchronized flag
#define RTC_FLAG_RTOFF (1 << 5) // RTC Operation OFF flag

#define RTC_BDCR_LSEON  (1 << 0)  // External low-speed oscillator enable
#define RTC_BDCR_LSERDY (1 << 1)  // External low-speed oscillator ready
#define RTC_BDCR_LSEBYP (1 << 2)  // External low-speed oscillator bypass
#define RTC_BDCR_RTCEN  (1 << 15) // RTC enable

#define RTC_BDRST (1 << 0) // Backup domain software reset

// RTC clock source selection
#define RTC_BDCR_RTCSEL_OFFSET 8
#define RTC_BDCR_RTCSEL_MASK   (3 << RTC_BDCR_RTCSEL_OFFSET)

// RTC clock calibration value
#define RTC_RTCCR_CAL_OFFSET 0
#define RTC_RTCCR_CAL_MASK   (0x7f << RTC_RTCCR_CAL_OFFSET)

#define RTC_RTCCR_CCO  (1 << 7) // Calibration clock output
#define RTC_RTCCR_ASOE (1 << 8) // Alarm or second output enable
#define RTC_RTCCR_ASOS (1 << 9) // Alarm or second output selection

#define RTC_RTCCR_OUTPUT_MASK (RTC_RTCCR_CCO | RTC_RTCCR_ASOE | RTC_RTCCR_ASOS)

#define RTC_LSB_MASK (0x0000FFFF) // RTC LSB Mask
#define RTC_PRLH_MASK (0x000F0000) // RTC prescaler MSB Mask

typedef enum
{
  RTC_CLK_SOURCE_NONE   = (0 << RTC_BDCR_RTCSEL_OFFSET),
  RTC_CLK_SOURCE_LSE    = (1 << RTC_BDCR_RTCSEL_OFFSET),
  RTC_CLK_SOURCE_LSI    = (2 << RTC_BDCR_RTCSEL_OFFSET),
  RTC_CLK_SOURCE_LOCAL  = (3 << RTC_BDCR_RTCSEL_OFFSET),
  RTC_CLK_SOURCE_LSEBYP = (4 << RTC_BDCR_RTCSEL_OFFSET) + RTC_CLK_SOURCE_LSE,
} RTC_ClkSourceTypeDef;

typedef enum
{
  RTC_OUTPUT_NONE   = 0,
  RTC_OUTPUT_CLOCK  = RTC_RTCCR_CCO,
  RTC_OUTPUT_ALARM  = RTC_RTCCR_ASOE,
  RTC_OUTPUT_SECOND = RTC_RTCCR_ASOE | RTC_RTCCR_ASOS,
} RTC_OutputTypeDef;

typedef struct
{
  __IO uint16_t REG;
  uint16_t RESERVED;
} BKP_DR_Typedef;

#define BKP_DATA_REGISTERS 16

typedef struct
{
  __IO uint16_t CRH;        // 0x00, RTC control register high
  __IO uint16_t RESERVED0;
  __IO uint16_t CRL;        // 0x04, RTC control register low
  __IO uint16_t RESERVED1;
  __IO uint16_t PRLH;       // 0x08, RTC prescaler load register high
  __IO uint16_t RESERVED2;
  __IO uint16_t PRLL;       // 0x0c, RTC prescaler load register low
  __IO uint16_t RESERVED3;
  __I  uint16_t DIVH;       // 0x10, RTC prescaler divider register high
  __IO uint16_t RESERVED4;
  __I  uint16_t DIVL;       // 0x14, RTC prescaler divider register low
  __IO uint16_t RESERVED5;
  __IO uint16_t CNTH;       // 0x18, RTC counter register high
  __IO uint16_t RESERVED6;
  __IO uint16_t CNTL;       // 0x1c, RTC counter register low
  __IO uint16_t RESERVED7;
  __IO uint16_t ALRH;       // 0x20, RTC alarm register high
  __IO uint16_t RESERVED8;
  __IO uint16_t ALRL;       // 0x24, RTC alarm register low
  __IO uint16_t RESERVED9;
  __IO uint16_t RCYC;       // 0x28, RTC read minimum cycle
  __IO uint16_t RESERVED10;
  __IO uint32_t RESERVED11; // 0x2C
  __IO uint16_t BDCR;       // 0x30, Backup domain control register
  __IO uint16_t BDRST;      // 0x32, Backup domain software reset
  __IO uint16_t IWDG;       // 0x34, IWDG registers
  __IO uint16_t RESERVED12; // 0x36
  __IO uint32_t RESERVED13; // 0x38
  __IO uint16_t RTCCR;      // 0x3C, RTC clock calibration register
  __IO uint16_t RESERVED14;
  __IO BKP_DR_Typedef BKP_DR[BKP_DATA_REGISTERS]; // 0x40, Backup domain data registers
} RTC_TypeDef;

#define RTC_BASE  (0x40000000)
#define RTC       ((RTC_TypeDef *) RTC_BASE)

// Any write to RTC/backup domain registger need to wait for RTOFF, including PRLH/PRLL, CNTH/CNTL, ALRH/ALRL, BDCR,
// IWDG, RTCCR, and BKP_DR
static inline void RTC_WaitForWrite(void) { while (!(RTC->CRL & RTC_FLAG_RTOFF)); }
#define RTC_WRITE_REG(REG, VALUE) { WRITE_REG(REG, VALUE); RTC_WaitForWrite(); }
#define RTC_MODIFY_BIT(REG, CLEARMASK, SETMASK) { MODIFY_BIT(REG, CLEARMASK, SETMASK); RTC_WaitForWrite(); }

void RTC_Reset(void);
void RTC_Init(RTC_ClkSourceTypeDef clk_source);
static inline void RTC_Disable(void)   { RTC_MODIFY_BIT(RTC->BDCR, RTC_BDCR_RTCEN, 0); }
static inline bool RTC_IsEnabled(void) { return RTC->BDCR & RTC_BDCR_RTCEN; }

static inline void RTC_EnableInt (uint16_t bits)   { RTC->CRH |=  bits; }
static inline void RTC_DisableInt(uint16_t bits)   { RTC->CRH &= ~bits; }
static inline bool RTC_IsEnabledInt(uint16_t bits) { return RTC->CRH & bits; }

static inline bool RTC_IsFlagActive(uint16_t bits) { return RTC->CRL & bits; }
static inline void RTC_ClearFlag(uint16_t bits) { RTC->CRL &= ~bits; }

static inline bool RTC_IsIntActive(uint16_t bits) { return RTC->CRH & bits & RTC->CRL; }
static inline void RTC_ClearInt(uint16_t bits) { RTC_ClearFlag(bits); }

static inline uint32_t RTC_GetCounter(void)   { return ((uint32_t)(RTC->CNTH) << 16) | RTC->CNTL; }
static inline uint32_t RTC_GetPrescaler(void) { return ((uint32_t)(RTC->PRLH) << 16) | RTC->PRLL; }
static inline uint32_t RTC_GetAlarm(void)     { return ((uint32_t)(RTC->ALRH) << 16) | RTC->ALRL; }
static inline uint32_t RTC_GetDivider(void)   { return ((uint32_t)(RTC->DIVH) << 16) | RTC->DIVL; }

static inline void RTC_SetCounter(uint32_t value)
{
  RTC_WRITE_REG(RTC->CNTH, value >> 16);
  RTC_WRITE_REG(RTC->CNTL, value & RTC_LSB_MASK);
}

static inline void RTC_SetPrescaler(uint32_t value)
{
  RTC_WRITE_REG(RTC->PRLH, value >> 16);
  RTC_WRITE_REG(RTC->PRLL, value & RTC_LSB_MASK);
}

static inline void RTC_SetAlarm(uint32_t value)
{
  RTC_WRITE_REG(RTC->ALRH, value >> 16);
  RTC_WRITE_REG(RTC->ALRL, value & RTC_LSB_MASK);
}

static inline void RTC_SetOutputMode(RTC_OutputTypeDef mode) { RTC_MODIFY_BIT(RTC->RTCCR, RTC_RTCCR_OUTPUT_MASK, mode); }
static inline void RTC_SetCalibrationValue(uint8_t value)    { RTC_MODIFY_BIT(RTC->RTCCR, RTC_RTCCR_CAL_MASK,   value); }

static inline void RTC_WriteBackupRegister(uint16_t idx, uint16_t value) { RTC_WRITE_REG(RTC->BKP_DR[idx].REG, value); }
static inline uint16_t RTC_ReadBackupRegister(uint16_t idx) { return RTC->BKP_DR[idx].REG; }


// Functions for RTC to handle BCD format (YYYY:MM:DD-HH:MM:SS)
#include <time.h>
uint32_t RTC_GetEpochSeconds(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);

#ifdef __cplusplus
}
#endif

#endif
