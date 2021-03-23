#ifndef _AGM_I2C_H
#define _AGM_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

typedef struct
{
  __IO uint32_t PRERLO; // 0x00, Prescaler register lo-byte
  __IO uint32_t PRERHI; // 0x04, Prescaler register hi-byte
  __IO uint32_t CTR;    // 0x08, Control register
  union {
    __O uint32_t TXR;   // 0x0c, Transmit register
    __I uint32_t RXR;   // 0x0c, Receive register
  };
  union {
    __O uint32_t CR;    // 0x10, Command register
    __I uint32_t SR;    // 0x10, Status register
  };
} I2C_TypeDef;

#define I2C_CTR_EN    (1 << 7) // Core enable
#define I2C_CTR_INTEN (1 << 6) // Interrupt enable

#define I2C_CR_IACK (1 << 0) // Interrupt acknowledge
#define I2C_CR_NACK (1 << 3) // When a receiver, send ACK(0) or NACK(1)
#define I2C_CR_WR   (1 << 4) // Write to slave
#define I2C_CR_RD   (1 << 5) // Read from slave
#define I2C_CR_STO  (1 << 6) // Generate stop condition
#define I2C_CR_STA  (1 << 7) // Generate (repeated) start condition

#define I2C_SR_IF    (1 << 0) // Interrupt flag. Set when one byte transfer is done or arbitration lost
#define I2C_SR_TIP   (1 << 1) // Transfer in progress
#define I2C_SR_AL    (1 << 5) // Arbitration lost
#define I2C_SR_BUSY  (1 << 6) // I2C bus busy
#define I2C_SR_RxACK (1 << 7) // 0: ACK from slave, 1: NACK from slave

#define I2C_WR_ADDR(__addr7) ((__addr7 << 1) | 0)
#define I2C_RD_ADDR(__addr7) ((__addr7 << 1) | 1)

void I2C_Init(I2C_TypeDef *i2c, uint32_t frequency);

static inline uint16_t I2C_GetPrescaler(I2C_TypeDef *i2c) { return ((uint16_t)(i2c->PRERHI) << 8) | i2c->PRERLO; }
static inline void I2C_SetPrescaler(I2C_TypeDef *i2c, uint16_t prescaler)
{
  i2c->PRERHI = prescaler >> 8;
  i2c->PRERLO = prescaler & 0xff;
}

static inline void I2C_Enable(I2C_TypeDef *i2c)  { i2c->CTR |=  I2C_CTR_EN; }
static inline void I2C_Disable(I2C_TypeDef *i2c) { i2c->CTR &= ~I2C_CTR_EN; }

static inline void I2C_EnableInt(I2C_TypeDef *i2c)  { i2c->CTR |=  I2C_CTR_INTEN; }
static inline void I2C_DisableInt(I2C_TypeDef *i2c) { i2c->CTR &= ~I2C_CTR_INTEN; }
static inline void I2C_ClearInt(I2C_TypeDef *i2c)   { i2c->CR = I2C_CR_IACK; }

static inline uint32_t I2C_GetStatus (I2C_TypeDef *i2c) { return i2c->SR; }

static inline bool I2C_IsIntActive      (I2C_TypeDef *i2c) { return i2c->SR & I2C_SR_IF;    }
static inline bool I2C_IsInTranser      (I2C_TypeDef *i2c) { return i2c->SR & I2C_SR_TIP;   }
static inline bool I2C_IsArbitrationLost(I2C_TypeDef *i2c) { return i2c->SR & I2C_SR_AL;    }
static inline bool I2C_IsBusy           (I2C_TypeDef *i2c) { return i2c->SR & I2C_SR_BUSY;  }
static inline bool I2C_IsRxNACK         (I2C_TypeDef *i2c) { return i2c->SR & I2C_SR_RxACK; }

static inline void I2C_WaitForTransfer(I2C_TypeDef *i2c) { while (I2C_IsInTranser(i2c)); }
static inline void I2C_WaitForBusy(I2C_TypeDef *i2c)     { while (I2C_IsBusy(i2c));      }

// These functions all wait for any on going transfer to finish first. They can block the cpu if they are called during
// an acitve transfer.
static inline void    I2C_SetCmd   (I2C_TypeDef *i2c, uint8_t cmd)  { I2C_WaitForTransfer(i2c); i2c->CR  = cmd;  }
static inline void    I2C_SetTxData(I2C_TypeDef *i2c, uint8_t data) { I2C_WaitForTransfer(i2c); i2c->TXR = data; }
static inline uint8_t I2C_GetRxData(I2C_TypeDef *i2c)               { I2C_WaitForTransfer(i2c); return i2c->RXR; }

void I2C_StartSend(I2C_TypeDef *i2c, uint8_t addr);
void I2C_SendData(I2C_TypeDef *i2c, uint8_t data);
void I2C_StopSend(I2C_TypeDef *i2c, uint8_t data);
void I2C_StartReceive(I2C_TypeDef *i2c, uint8_t addr);
void I2C_ReceiveData(I2C_TypeDef *i2c);
void I2C_StopReceive(I2C_TypeDef *i2c);

static inline void I2C_Stop(I2C_TypeDef *i2c) { I2C_SetCmd(i2c, I2C_CR_STO | I2C_CR_NACK); } // Stop without any other action

// Functions that will wait for the read transfer to complete and return received data
static inline uint8_t I2C_ReceiveDataWait(I2C_TypeDef *i2c)
{
  I2C_ReceiveData(i2c);
  I2C_WaitForTransfer(i2c);
  return i2c->RXR;
}
static inline uint8_t I2C_StopReceiveWait(I2C_TypeDef *i2c)
{
  I2C_StopReceive(i2c);
  I2C_WaitForTransfer(i2c);
  return i2c->RXR;
}

#ifdef __cplusplus
}
#endif

#endif
