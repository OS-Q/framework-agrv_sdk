#ifndef _AGM_MAC_H
#define _AGM_MAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

typedef struct
{
  __IO uint32_t CTRL;      // 0x00, Control register
  __IO uint32_t STAT;      // 0x04, Status register
  __IO uint32_t MACMSB;    // 0x08, Mac address MSB
  __IO uint32_t MACLSB;    // 0x0C, Mac address LSB
  __IO uint32_t MDIO;      // 0x10, MDIO control and status register
  __IO uint32_t TXBASE;    // 0x14, Transmit descriptor table base address
  __IO uint32_t RXBASE;    // 0x18, Receive descriptor table base address
  __IO uint32_t RESERVED0; // 0x1C, Reserved
  __IO uint32_t HTMSB;     // 0x20, Hash table MSB
  __IO uint32_t HTLSB;     // 0x24, Hash table LSB
} MAC_TypeDef;

#define MAC_CTRL_TX_EN        (1 << 0)  // Transmit enable
#define MAC_CTRL_RX_EN        (1 << 1)  // Receive enable
#define MAC_CTRL_TX_INTEN     (1 << 2)  // Transmit interrupt enable
#define MAC_CTRL_RX_INTEN     (1 << 3)  // Receive interrupt enable
#define MAC_CTRL_DUPLEX       (1 << 4)  // 0: half duplex, 1: full duplex
#define MAC_CTRL_PROM         (1 << 5)  // Promiscuous mode
#define MAC_CTRL_RESET        (1 << 6)  // Reset, self clearing
#define MAC_CTRL_SPEED        (1 << 7)  // 0: 10M, 1: 100M
#define MAC_CTRL_PHY_INTEN    (1 << 10) // PHY status change interrupt enable
#define MAC_CTRL_MULTICAST_EN (1 << 11) // Multicast enable
#define MAC_CTRL_RMII_MODE    (1 << 16) // RMII mode

// Status registers are cleared when written with a 1
#define MAC_STAT_RX_ERR    (1 << 0) // Receive error
#define MAC_STAT_TX_ERR    (1 << 1) // Transmit error
#define MAC_STAT_RX_INT    (1 << 2) // Receive interrupt
#define MAC_STAT_TX_INT    (1 << 3) // Transmit interrupt
#define MAC_STAT_RX_AHBERR (1 << 4) // Receive AHB error
#define MAC_STAT_TX_AHBERR (1 << 5) // Transmit AHB error
#define MAC_STAT_TOO_SMALL (1 << 6) // Too small. Packet received is smaller than minimum size
#define MAC_STAT_INV_ADDR  (1 << 7) // Invalid address
#define MAC_STAT_PHY_STAT  (1 << 8) // PHY status change

#define MAC_STAT_CLEAR_MASK 0x1ff // Used to clear all MAC_STAT bits

#define MAC_MDIO_WRITE     (1 << 0) // MDIO write
#define MAC_MDIO_READ      (1 << 1) // MDIO read
#define MAC_MDIO_LINK_FAIL (1 << 2) // Link fail, read only
#define MAC_MDIO_BUSY      (1 << 3) // MDIO busy, read only

#define MAC_MDIO_MDCSC_OFFSET   4
#define MAC_MDIO_REGADDR_OFFSET 6
#define MAC_MDIO_PHYADDR_OFFSET 11
#define MAC_MDIO_DATA_OFFSET    16

#define MAC_MDIO_MDCSC_MASK   (0x3    << MAC_MDIO_MDCSC_OFFSET)
#define MAC_MDIO_REGADDR_MASK (0x1f   << MAC_MDIO_REGADDR_OFFSET)
#define MAC_MDIO_PHYADDR_MASK (0x1f   << MAC_MDIO_PHYADDR_OFFSET)
#define MAC_MDIO_DATA_MASK    (0xffff << MAC_MDIO_DATA_OFFSET)

#define MAC_PHY_REG_CTRL 0  // Basic Mode Control
#define MAC_PHY_REG_STAT 1  // Basic Mode Status
#define MAC_PHY_REG_PSMR 24 // Power Saving Mode
#define MAC_PHY_REG_INT  30 // Interrupt Indicators and SNR Display
#define MAC_PHY_REG_PAGE 31 // Page Select
#define MAC_PHY_REG_RMSR 16 // Page 7, RMII Mode Setting
#define MAC_PHY_REG_IWL  19 // Page 7, Interrupt, WOL Enable, and LEDs

#define MAC_PHY_CTRL_DUPLEX     (1 << 8)
#define MAC_PHY_CTRL_AUTONEG_EN (1 << 12)
#define MAC_PHY_CTRL_SPEED      (1 << 13)
#define MAC_PHY_CTRL_LOOPBACK   (1 << 14)
#define MAC_PHY_CTRL_RESET      (1 << 15)

#define MAC_PHY_STAT_LINK_STATUS  (1 << 2)
#define MAC_PHY_STAT_AUTONEG_DONE (1 << 5)

#define MAC_PHY_INT_LINK_CHG    (1 << 11)
#define MAC_PHY_INT_DUPLEX_CHG  (1 << 13)
#define MAC_PHY_INT_SPEED_CHG   (1 << 14)
#define MAC_PHY_INT_AUTONEG_ERR (1 << 15)

#define MAC_PHY_RMSR_RMII_OFFSET  3
#define MAC_PHY_RMSR_RMII_MODE    (1 << MAC_PHY_RMSR_RMII_OFFSET)
#define MAC_PHY_RMSR_RMII_CLKDIR  (1 << 12)
#define MAC_PHY_RMSR_RMII_CLK_OUT (0 << 12)
#define MAC_PHY_RMSR_RMII_CLK_IN  (1 << 12)

#define MAC_PHY_IWL_LED_SEL_OFFSET 4
#define MAC_PHY_IWL_LED_SEL     (3 << MAC_PHY_IWL_LED_SEL_OFFSET)
#define MAC_PHY_IWL_INT_DUPCHG  (1 << 12)
#define MAC_PHY_IWL_INT_LINKCHG (1 << 13)

#define MAC_PHY_PSMR_ENPWRSAVE (1 << 15)

// Common to both TX and RX descriptors
#define MAC_DESC_LENGTH_MASK 0x7ff
#define MAC_DESC_EN          (1 << 11)
#define MAC_DESC_WRAP        (1 << 12)
#define MAC_DESC_INTEN       (1 << 13)

#define MAC_DESC_BITS        10
#define MAC_DESC_MAX         (1 << MAC_DESC_BITS)       // 1024
#define MAC_DESC_ALIGN_BITS  (MAC_DESC_BITS + 3 - 5)    // 8
#define MAC_DESC_MIN_ALIGN   (1 << MAC_DESC_ALIGN_BITS) // 256
#define MAC_DESC_WRAP_OFFSET 27
#define MAC_GET_DESC_WRAP(__desc) ((((uint32_t)__desc >> MAC_DESC_ALIGN_BITS) & 0x1f) << MAC_DESC_WRAP_OFFSET | MAC_DESC_WRAP)
// Helper to dertermin the alignment of rx/tx descriptor tables. Depending on the number of desired descriptors, the
// minimum alignment is 256 bytes (for 32 descriptors) and the maximum alignment is 8K bytes (for 1024 descriptors)
#define MAC_GET_DESC_ALIGN(__NUM_DESC) MAX(__NUM_DESC * sizeof(MAC_DescriptorTypeDef), MAC_DESC_MIN_ALIGN)

// For TX descriptors
#define MAC_TX_DESC_UNDERRUN_ERR (1 << 14)
#define MAC_TX_DESC_LIMIT_ERR    (1 << 15)

// For RX descriptors
#define MAC_RX_DESC_ALIGN_ERR   (1 << 14)
#define MAC_RX_DESC_TOO_LONG    (1 << 15)
#define MAC_RX_DESC_CRC_ERR     (1 << 16)
#define MAC_RX_DESC_OVERRUN_ERR (1 << 17)
#define MAC_RX_DESC_LENGTH_ERR  (1 << 18)
#define MAC_RX_DESC_MULTI_CAST  (1 << 26)

typedef enum
{
  MAC_AUTO_NEG_DISABLE = 0,
  MAC_AUTO_NEG_ENABLE  = MAC_PHY_CTRL_AUTONEG_EN,
} MAC_AutoNegTypeDef;

typedef enum
{
  MAC_HALF_DUPLEX = 0,
  MAC_FULL_DUPLEX = MAC_CTRL_DUPLEX,
} MAC_DuplexTypeDef;

typedef enum
{
  MAC_SPEED_10M = 0,
  MAC_SPEED_100M = MAC_CTRL_SPEED,
} MAC_SpeedTypeDef;

typedef enum
{
  MAC_MEDIA_INTERFACE_MII  = 0,
  MAC_MEDIA_INTERFACE_RMII = MAC_CTRL_RMII_MODE,
} MAC_MediaInterfaceTypeDef;

typedef enum
{
  MAC_LOOPBACK_DISABLE = 0,
  MAC_LOOPBACK_ENABLE  = MAC_PHY_CTRL_LOOPBACK,
} MAC_LoopbackTypeDef;

typedef enum
{
  MAC_MDIO_MDCSC128 = 0 << MAC_MDIO_MDCSC_OFFSET,
  MAC_MDIO_MDCSC64  = 1 << MAC_MDIO_MDCSC_OFFSET,
  MAC_MDIO_MDCSC32  = 2 << MAC_MDIO_MDCSC_OFFSET,
  MAC_MDIO_MDCSC16  = 3 << MAC_MDIO_MDCSC_OFFSET,
} MAC_MDC_ScalerTypeDef;

static inline void MAC_StartTx(MAC_TypeDef *mac) { mac->CTRL |=  MAC_CTRL_TX_EN;    }
static inline void MAC_StartRx(MAC_TypeDef *mac) { mac->CTRL |=  MAC_CTRL_RX_EN;    }
static inline void MAC_Reset(MAC_TypeDef *mac)   { mac->CTRL |=  MAC_CTRL_RESET;    }

static inline bool MAC_IsTxEnabled(MAC_TypeDef *mac)    { return mac->CTRL & MAC_CTRL_TX_EN; }
static inline bool MAC_IsRxEnabled(MAC_TypeDef *mac)    { return mac->CTRL & MAC_CTRL_RX_EN; }
static inline bool MAC_IsResetEnabled(MAC_TypeDef *mac) { return mac->CTRL & MAC_CTRL_RESET; }

static inline void MAC_WaitForTx(MAC_TypeDef    *mac) { while (MAC_IsTxEnabled(mac));    }
static inline void MAC_WaitForRx(MAC_TypeDef    *mac) { while (MAC_IsRxEnabled(mac));    }
static inline void MAC_WaitForReset(MAC_TypeDef *mac) { while (MAC_IsResetEnabled(mac)); }

static inline void MAC_EnableIntTx(MAC_TypeDef *mac)   { mac->CTRL |= MAC_CTRL_TX_INTEN;   }
static inline void MAC_EnableIntRx(MAC_TypeDef *mac)   { mac->CTRL |= MAC_CTRL_RX_INTEN;   }
static inline void MAC_EnableIntPhy(MAC_TypeDef *mac)  { mac->CTRL |= MAC_CTRL_PHY_INTEN;  }
static inline void MAC_DisableIntTx(MAC_TypeDef *mac)  { mac->CTRL &= ~MAC_CTRL_TX_INTEN;  }
static inline void MAC_DisableIntRx(MAC_TypeDef *mac)  { mac->CTRL &= ~MAC_CTRL_RX_INTEN;  }
static inline void MAC_DisableIntPhy(MAC_TypeDef *mac) { mac->CTRL &= ~MAC_CTRL_PHY_INTEN; }

static inline void MAC_EnablePromMode(MAC_TypeDef *mac)   { mac->CTRL |=  MAC_CTRL_PROM; }
static inline void MAC_DisablePromMode(MAC_TypeDef *mac)  { mac->CTRL &= ~MAC_CTRL_PROM; }
static inline void MAC_EnableMultiCast(MAC_TypeDef *mac)  { mac->CTRL |=  MAC_CTRL_MULTICAST_EN; }
static inline void MAC_DisableMultiCast(MAC_TypeDef *mac) { mac->CTRL &= ~MAC_CTRL_MULTICAST_EN; }

static inline uint32_t MAC_GetStatus(MAC_TypeDef *mac) { return mac->STAT; }
static inline void MAC_ClearStatus(MAC_TypeDef *mac, uint32_t bits) { mac->STAT = bits; }
static inline void MAC_ClearStatusAll(MAC_TypeDef *mac) { MAC_ClearStatus(mac, MAC_STAT_CLEAR_MASK); }

static inline void MAC_WaitForMdio(MAC_TypeDef *mac) { while (mac->MDIO & MAC_MDIO_BUSY); }

typedef struct
{
  __IO uint32_t Ctrl;
  __IO uint32_t Addr; // Address must be 4-byte aligned
} MAC_DescriptorTypeDef;

typedef struct
{
  MAC_AutoNegTypeDef        AutoNegotiation;
  MAC_DuplexTypeDef         DuplexMode;
  MAC_SpeedTypeDef          Speed;
  MAC_MediaInterfaceTypeDef MediaInterface;
  MAC_LoopbackTypeDef       LoopbackMode;
  MAC_MDC_ScalerTypeDef     MdcScaler;
  bool                      WaitAutoNegotiation;
  uint8_t                   PhyAddress;
  uint8_t                   MacAddress[6];
} MAC_InitTypeDef;

typedef struct
{
  MAC_TypeDef           *Instance;
  MAC_InitTypeDef       Init;
  MAC_DescriptorTypeDef *TxDesc;
  MAC_DescriptorTypeDef *RxDesc;
  uint16_t              TxNumDesc; // Must not exceed MAC_DESC_MAX
  uint16_t              RxNumDesc; // Must not exceed MAC_DESC_MAX
  uint16_t              TxPointer;
  uint16_t              RxPointer;
} MAC_HandleTypeDef;

void MAC_MdioWrite(MAC_HandleTypeDef *hmac, uint8_t reg_addr, uint16_t data);
uint16_t MAC_MdioRead(MAC_HandleTypeDef *hmac, uint8_t reg_addr);

void MAC_StructInit(MAC_InitTypeDef *init);
void MAC_HandleInit(MAC_HandleTypeDef *hmac, MAC_DescriptorTypeDef *TxDesc, int TxNumDesc, MAC_DescriptorTypeDef *RxDesc, int RxNumDesc);

ReturnCodeTypedef MAC_Init(MAC_HandleTypeDef *hmac);
ReturnCodeTypedef MAC_UpdateLink(MAC_HandleTypeDef *hmac);

// Buffers used in TX/RX descriptors must be 4-byte aligned
void MAC_Transmit(MAC_HandleTypeDef *hmac, const uint32_t *buf, int length);
void MAC_Receive (MAC_HandleTypeDef *hmac, uint32_t *buf);

// Descriptor functions
static inline bool MAC_IsDescEnabled(MAC_DescriptorTypeDef *desc)
{
  return desc->Ctrl & MAC_DESC_EN;
}
static inline uint16_t MAC_GetDescLength(MAC_DescriptorTypeDef *desc)
{
  return desc->Ctrl & MAC_DESC_LENGTH_MASK;
}
static inline void MAC_WaitForDesc(MAC_DescriptorTypeDef *desc)
{
  while (MAC_IsDescEnabled(desc));
}
uint32_t MAC_GetTxDescCtrl(MAC_HandleTypeDef *hmac, int length, bool wrap);
uint32_t MAC_GetRxDescCtrl(MAC_HandleTypeDef *hmac, bool wrap);

#ifdef __cplusplus
}
#endif

#endif
