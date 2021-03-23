#include "rtc.h"

void RTC_Reset(void)
{
  // Reset RTC domain registers, including IWDG and backup registers
  RTC->BDRST |=  RTC_BDRST;
  RTC->BDRST &= ~RTC_BDRST;

  // Reset core domain registers
  RTC->CRH  = 0;
  RTC->CRL  = 0;
}

void RTC_Init(RTC_ClkSourceTypeDef clk_source)
{
  uint16_t bdcr = RTC_BDCR_RTCEN | (clk_source & RTC_BDCR_RTCSEL_MASK);
  bool waitLse = false;
  switch (clk_source) {
  case RTC_CLK_SOURCE_LSEBYP:
    bdcr |= RTC_BDCR_LSEBYP;
  case RTC_CLK_SOURCE_LSE:
    bdcr |= RTC_BDCR_LSEON;
    waitLse = true;
    break;
  default:
    break;
  }
  RTC_WRITE_REG(RTC->BDCR, bdcr);
  if (waitLse) {
    while (!READ_BIT(RTC->BDCR, RTC_BDCR_LSERDY));
  }
}


// Functions for RTC to handle BCD format (YYYY:MM:DD-HH:MM:SS)
#define  DAYS_PER_YEAR      (365)
#define  SECS_PER_MIN       (60)
#define  SECS_PER_HOUR      (SECS_PER_MIN  * 60)
#define  SECS_PER_DAY       (SECS_PER_HOUR * 24)
#define  EPOCH_YEAR         (1970)
#define  IS_LEAP_YEAR(year) (!((year) % 4) && (((year) % 100) || !((year) % 400)))

static const int DAYS_PER_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

uint32_t RTC_GetDayOfYear(uint32_t year, uint32_t month, uint32_t day)
{
  uint32_t yday = day - 1;
  for (unsigned int i = 0; i < month - 1; ++i) {
    yday += DAYS_PER_MONTH[i];
    if (i == 1 && IS_LEAP_YEAR(year)) {
      ++yday;
    }
  }
  return yday;
}

// This is a light version of mktime in time.h. The returned value of seconds can be set as RTC counter value
uint32_t RTC_GetEpochSeconds(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second)
{
  uint32_t yday = RTC_GetDayOfYear(year, month, day);
  uint32_t secs = second + minute * SECS_PER_MIN + hour * SECS_PER_HOUR + yday * SECS_PER_DAY;
  uint32_t leapdays = (year - EPOCH_YEAR + 1) / 4 - ((year - EPOCH_YEAR + 69) / 100) + ((year - EPOCH_YEAR + 369) / 400);
  secs += (year - EPOCH_YEAR) * SECS_PER_DAY * DAYS_PER_YEAR;
  secs += leapdays * SECS_PER_DAY;
  return secs;
}

