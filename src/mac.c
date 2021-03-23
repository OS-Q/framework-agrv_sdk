#include "alta.h"

// Timeout in millisecond
#ifndef MAC_TIMEOUT_RESET
#define MAC_TIMEOUT_RESET   500
#endif
#ifndef MAC_TIMEOUT_LINK
#define MAC_TIMEOUT_LINK    5000
#endif
#ifndef MAC_TIMEOUT_AUTONEG
#define MAC_TIMEOUT_AUTONEG 5000
#endif

void MAC_MdioWrite(MAC_HandleTypeDef *hmac, uint8_t reg_addr, uint16_t data)
{
  MAC_WaitForMdio(hmac->Instance);
  hmac->Instance->MDIO = (data << MAC_MDIO_DATA_OFFSET) |(hmac->Init.PhyAddress << MAC_MDIO_PHYADDR_OFFSET) | (reg_addr << MAC_MDIO_REGADDR_OFFSET) | hmac->Init.MdcScaler | MAC_MDIO_WRITE;
  MAC_WaitForMdio(hmac->Instance);
}

uint16_t MAC_MdioRead(MAC_HandleTypeDef *hmac, uint8_t reg_addr)
{
  MAC_WaitForMdio(hmac->Instance);
  hmac->Instance->MDIO = (hmac->Init.PhyAddress << MAC_MDIO_PHYADDR_OFFSET) | (reg_addr << MAC_MDIO_REGADDR_OFFSET) | hmac->Init.MdcScaler | MAC_MDIO_READ;
  MAC_WaitForMdio(hmac->Instance);
  return (hmac->Instance->MDIO & MAC_MDIO_DATA_MASK) >> MAC_MDIO_DATA_OFFSET;
}

void MAC_StructInit(MAC_InitTypeDef *init)
{
  memset(init, 0, sizeof(MAC_InitTypeDef));
  init->AutoNegotiation     = MAC_AUTO_NEG_ENABLE;
  init->WaitAutoNegotiation = false;
  init->DuplexMode          = MAC_FULL_DUPLEX;
  init->Speed               = MAC_SPEED_100M;
  init->MediaInterface      = MAC_MEDIA_INTERFACE_RMII;
  init->LoopbackMode        = MAC_LOOPBACK_DISABLE;

  // Assume maximum MDC frequency is 2.5MHz. MdcScaler can be changed to achieve higher or lower MDC frequency.
  uint32_t freq = SYS_GetSysClkFreq();
  if (freq > 160000000) {
    init->MdcScaler = MAC_MDIO_MDCSC128;
  } else if (freq > 80000000) {
    init->MdcScaler = MAC_MDIO_MDCSC64;
  } else if (freq > 40000000) {
    init->MdcScaler = MAC_MDIO_MDCSC32;
  } else {
    init->MdcScaler = MAC_MDIO_MDCSC16;
  }
}

void MAC_HandleInit(MAC_HandleTypeDef *hmac, MAC_DescriptorTypeDef *TxDesc, int TxNumDesc, MAC_DescriptorTypeDef *RxDesc, int RxNumDesc)
{
  // TxDesc and RxDesc should be aligned using the helper macro MAC_GET_DESC_ALIGN.
  ASSERT(((uint32_t)TxDesc & (MAC_GET_DESC_ALIGN(TxNumDesc) - 1)) == 0);
  ASSERT(((uint32_t)RxDesc & (MAC_GET_DESC_ALIGN(RxNumDesc) - 1)) == 0);
  hmac->Instance  = MAC0;
  hmac->TxPointer = 0;
  hmac->RxPointer = 0;
  hmac->TxDesc    = TxDesc;
  hmac->RxDesc    = RxDesc;
  hmac->TxNumDesc = TxNumDesc;
  hmac->RxNumDesc = RxNumDesc;
  MAC_StructInit(&hmac->Init);
}

ReturnCodeTypedef MAC_Init(MAC_HandleTypeDef *hmac)
{
  MAC_TypeDef *mac = hmac->Instance;

  MAC_Reset(mac);
  MAC_WaitForReset(mac);

  uint16_t mdio;
  MAC_MdioWrite(hmac, MAC_PHY_REG_CTRL, MAC_PHY_CTRL_RESET | hmac->Init.AutoNegotiation | hmac->Init.LoopbackMode);
  uint32_t tickstart = UTIL_GetTick();
  while ((mdio = MAC_MdioRead(hmac, MAC_PHY_REG_CTRL)) & MAC_PHY_CTRL_RESET) { // Wait for reset to self clear
    if (UTIL_GetTick() - tickstart > MAC_TIMEOUT_RESET) {
      return RET_ERR;
    }
  }

  if (hmac->Init.AutoNegotiation) {
    tickstart = UTIL_GetTick();
    while (!((mdio = MAC_MdioRead(hmac, MAC_PHY_REG_STAT)) & MAC_PHY_STAT_AUTONEG_DONE)) {
      if (!hmac->Init.WaitAutoNegotiation || UTIL_GetTick() - tickstart > MAC_TIMEOUT_AUTONEG) {
        break;
      }
    }
    if (mdio & MAC_PHY_STAT_AUTONEG_DONE) {
      // Use auto negotiation result to update duplex mode and speed
      mdio = MAC_MdioRead(hmac, MAC_PHY_REG_CTRL);
      hmac->Init.DuplexMode = (mdio & MAC_PHY_CTRL_DUPLEX) ? MAC_FULL_DUPLEX : MAC_HALF_DUPLEX;
      hmac->Init.Speed      = (mdio & MAC_PHY_CTRL_SPEED)  ? MAC_SPEED_100M  : MAC_SPEED_10M;
    }
  } else {
    MAC_MdioWrite(hmac, MAC_PHY_REG_CTRL, (hmac->Init.DuplexMode << 4) | (hmac->Init.Speed << 6) | hmac->Init.LoopbackMode);
    while (!((mdio = MAC_MdioRead(hmac, MAC_PHY_REG_STAT)) & MAC_PHY_STAT_LINK_STATUS)) {
      if (UTIL_GetTick() - tickstart > MAC_TIMEOUT_LINK) {
        break;
      }
    }
  }

  hmac->Instance->CTRL   = hmac->Init.DuplexMode | hmac->Init.Speed | hmac->Init.MediaInterface;
  hmac->Instance->MACMSB = hmac->Init.MacAddress[0] << 8 | hmac->Init.MacAddress[1];
  hmac->Instance->MACLSB = hmac->Init.MacAddress[2] << 24 | hmac->Init.MacAddress[3] << 16 | hmac->Init.MacAddress[4] << 8 | hmac->Init.MacAddress[5];
  hmac->Instance->TXBASE = (uint32_t)hmac->TxDesc;
  hmac->Instance->RXBASE = (uint32_t)hmac->RxDesc;

  return RET_OK;
}

ReturnCodeTypedef MAC_UpdateLink(MAC_HandleTypeDef *hmac)
{
  // Can be called whenever link status changed to udpate duplex and speed
  if (hmac->Init.AutoNegotiation &&(MAC_MdioRead(hmac, MAC_PHY_REG_STAT) & MAC_PHY_STAT_AUTONEG_DONE)) {
    uint16_t mdio = MAC_MdioRead(hmac, MAC_PHY_REG_CTRL);
    hmac->Init.DuplexMode = (mdio & MAC_PHY_CTRL_DUPLEX) ? MAC_FULL_DUPLEX : MAC_HALF_DUPLEX;
    hmac->Init.Speed      = (mdio & MAC_PHY_CTRL_SPEED)  ? MAC_SPEED_100M  : MAC_SPEED_10M;
    MODIFY_REG(hmac->Instance->CTRL, MAC_CTRL_DUPLEX | MAC_CTRL_SPEED | MAC_CTRL_RMII_MODE,
               hmac->Init.DuplexMode | hmac->Init.Speed | hmac->Init.MediaInterface);
    return RET_OK;
  }
  return RET_ERR;
}

uint32_t MAC_GetTxDescCtrl(MAC_HandleTypeDef *hmac, int length, bool wrap) {
  uint32_t ctrl = length | MAC_DESC_EN | MAC_DESC_INTEN;
  if (wrap) {
    ctrl |= MAC_GET_DESC_WRAP(hmac->TxDesc);
  }
  return ctrl;
}

uint32_t MAC_GetRxDescCtrl(MAC_HandleTypeDef *hmac, bool wrap)
{
  uint32_t ctrl = MAC_DESC_EN | MAC_DESC_INTEN;
  if (wrap) {
    ctrl |= MAC_GET_DESC_WRAP(hmac->RxDesc);
  }
  return ctrl;
}

void MAC_Transmit(MAC_HandleTypeDef *hmac, const uint32_t *buf, int length)
{
  MAC_DescriptorTypeDef *desc = &hmac->TxDesc[hmac->TxPointer];
  MAC_WaitForDesc(desc);
  bool wrap = ++hmac->TxPointer == hmac->TxNumDesc;
  if (wrap) {
    hmac->TxPointer = 0; // Descriptor will wrap from hmac->TxDesc
  }
  desc->Addr = (uint32_t)buf;
  desc->Ctrl = MAC_GetTxDescCtrl(hmac, length, wrap);
  MAC_StartTx(hmac->Instance);
}

void MAC_Receive(MAC_HandleTypeDef *hmac, uint32_t *buf)
{
  MAC_DescriptorTypeDef *desc = &hmac->RxDesc[hmac->RxPointer];
  MAC_WaitForDesc(desc);
  bool wrap = ++hmac->RxPointer == hmac->RxNumDesc;
  if (wrap) {
    hmac->RxPointer = 0; // Descriptor will wrap from hmac->RxDesc
  }
  desc->Addr = (uint32_t) buf;
  desc->Ctrl = MAC_GetRxDescCtrl(hmac, wrap);
  MAC_StartRx(hmac->Instance);
}

