#include "i2c.h"
#include "system.h"

void I2C_Init(I2C_TypeDef *i2c, uint32_t frequency)
{
  uint16_t prescaler = SYS_GetPclkFreq() / frequency / 5 - 1;
  I2C_SetPrescaler(i2c, prescaler);
}

void I2C_StartSend(I2C_TypeDef *i2c, uint8_t addr)
{
  I2C_WaitForTransfer(i2c); // Make sure no transfer is in progress
  I2C_SetTxData(i2c, I2C_WR_ADDR(addr));
  I2C_SetCmd(i2c, I2C_CR_WR | I2C_CR_STA);
}

void I2C_SendData(I2C_TypeDef *i2c, uint8_t data)
{
  I2C_WaitForTransfer(i2c);
  I2C_SetTxData(i2c, data);
  I2C_SetCmd(i2c, I2C_CR_WR);
}

void I2C_StopSend(I2C_TypeDef *i2c, uint8_t data)
{
  I2C_WaitForTransfer(i2c);
  I2C_SetTxData(i2c, data);
  I2C_SetCmd(i2c, I2C_CR_WR | I2C_CR_STO);
}

void I2C_StartReceive(I2C_TypeDef *i2c, uint8_t addr)
{
  I2C_WaitForTransfer(i2c);
  I2C_SetTxData(i2c, I2C_RD_ADDR(addr));
  I2C_SetCmd(i2c, I2C_CR_WR | I2C_CR_STA);
}

// Send the receive commands. Data can be read from RXR after TIP bit is cleared
void I2C_ReceiveData(I2C_TypeDef *i2c)
{ 
  I2C_WaitForTransfer(i2c);
  I2C_SetCmd(i2c, I2C_CR_RD);
}

void I2C_StopReceive(I2C_TypeDef *i2c)
{
  I2C_WaitForTransfer(i2c);
  I2C_SetCmd(i2c, I2C_CR_RD | I2C_CR_STO | I2C_CR_NACK);
}
