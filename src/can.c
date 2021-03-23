#include "can.h"

void CAN_Filter_StructInit(CAN_FilterConfigTypeDef *init)
{
  init->FilterMode = CAN_FILTER_SINGLE;
  for (int i = 0; i < 4; ++i) {
    init->FilterMask[i] = CAN_FILTER_DONT_CARE; // Accept message with any identifier
    init->FilterCode[i] = 0x00;
  }
}

// Single filter for standard frame format. Can match ID, RTR, and data bytes 1 and 2
void CAN_SetStandardSingleFilter(CAN_FilterConfigTypeDef *init, uint16_t id_mask, uint16_t id_code,
                                 uint16_t data_mask, uint16_t data_code, uint8_t rtr_mask, uint8_t rtr_code)
{
  init->FilterMode = CAN_FILTER_SINGLE;
  init->FilterMask[0] = id_mask >> 3;
  init->FilterCode[0] = id_code >> 3;
  init->FilterMask[1] = (id_mask << 5) | (rtr_mask ? (1 << 4) : 0);
  init->FilterCode[1] = (id_code << 5) | (rtr_code ? (1 << 4) : 0);
  init->FilterMask[2] = data_mask >> 8; // Data byte 1
  init->FilterCode[2] = data_code >> 8; // Data byte 1
  init->FilterMask[3] = data_mask;      // Data byte 2
  init->FilterCode[3] = data_code;      // Data byte 2
}

// Dual filter for standard frame format. Filter 0 can match ID, RTR, and data byte 1. Filter 2 can match ID and RTR
void CAN_SetStandardDualFilter(CAN_FilterConfigTypeDef *init, uint16_t id_mask0, uint16_t id_code0,
                               uint8_t data_mask0, uint8_t data_code0, uint8_t rtr_mask0, uint8_t rtr_code0,
                               uint16_t id_mask1,  uint16_t id_code1,  uint8_t rtr_mask1, uint8_t rtr_code1)
{
  init->FilterMode = CAN_FILTER_DUAL;
  init->FilterMask[0] = id_mask0 >> 3;
  init->FilterCode[0] = id_code0 >> 3;
  init->FilterMask[1] = (id_mask0 << 5) | (rtr_mask0 ? (1 << 4) : 0) | (data_mask0 >> 4);
  init->FilterCode[1] = (id_code0 << 5) | (rtr_code0 ? (1 << 4) : 0) | (data_code0 >> 4);
  init->FilterMask[2] = id_mask1 >> 3;
  init->FilterCode[2] = id_code1 >> 3;
  init->FilterMask[3] = (id_mask1 << 5) | (rtr_mask1 ? (1 << 4) : 0) | (data_mask0 & 0xf);
  init->FilterCode[3] = (id_code1 << 5) | (rtr_code1 ? (1 << 4) : 0) | (data_code0 & 0xf);
}

// Single filter for extended frame format. Can match ID and RTR
void CAN_SetExtendedSingleFilter(CAN_FilterConfigTypeDef *init, uint32_t id_mask, uint32_t id_code,
                                 uint8_t rtr_mask, uint8_t rtr_code)
{
  init->FilterMode = CAN_FILTER_SINGLE;
  init->FilterMask[0] = id_mask >> 21;
  init->FilterCode[0] = id_code >> 21;
  init->FilterMask[1] = id_mask >> 13;
  init->FilterCode[1] = id_code >> 13;
  init->FilterMask[2] = id_mask >> 5;
  init->FilterCode[2] = id_code >> 5;
  init->FilterMask[3] = (id_mask << 3) | (rtr_mask ? (1 << 2) : 0);
  init->FilterCode[3] = (id_code << 3) | (rtr_code ? (1 << 2) : 0);
}

// Dual filter for extended frame format. Each filter can match the upper 16 bits of the 29-bit ID
void CAN_SetExtendedDualFilter(CAN_FilterConfigTypeDef *init, uint32_t id_mask0, uint32_t id_code0,
                               uint32_t id_mask1, uint32_t id_code1)
{
  init->FilterMode = CAN_FILTER_DUAL;
  init->FilterMask[0] = id_mask0 >> 21;
  init->FilterCode[0] = id_code0 >> 21;
  init->FilterMask[1] = id_mask0 >> 13;
  init->FilterCode[1] = id_code0 >> 13;
  init->FilterMask[2] = id_mask1 >> 21;
  init->FilterCode[2] = id_code1 >> 21;
  init->FilterMask[3] = id_mask1 >> 13;
  init->FilterCode[3] = id_code1 >> 13;
}

void CAN_StructInit(CAN_InitTypeDef *init)
{
  init->Prescaler  = 0;
  init->SJW        = CAN_SJW_1TQ;
  init->TSeg1      = CAN_TSEG1_1TQ;
  init->TSeg2      = CAN_TSEG2_1TQ;
  init->Sampling   = CAN_SAMPLING_1;

  CAN_Filter_StructInit(&init->FilterConfig);
}

void CAN_Init(CAN_TypeDef *can, CAN_InitTypeDef *init)
{
  can->MOD = CAN_MOD_RESET;
  can->BTR0 = init->Prescaler | init->SJW;
  can->BTR1 = init->TSeg1 | init->TSeg2 | init->Sampling;
  for (int i = 0; i < 4; ++i) {
    can->AMR[i] = init->FilterConfig.FilterMask[i];
    can->ACR[i] = init->FilterConfig.FilterCode[i];
  }
  can->OCR = CAN_OUTPUT_MODE_NORMAL;
  can->RXERR = 0;
  can->TXERR = 0;

  can->MOD = init->FilterConfig.FilterMode; // Will also clear the reset bit
}

void CAN_PrepareTx(CAN_TypeDef *can, CAN_TxMessageTypeDef *tx_msg)
{
  CAN_WaitForTx(can);
  can->TXFRAME = tx_msg->FF | tx_msg->RTR | tx_msg->DLC;
  int data_idx;
  if (tx_msg->FF == CAN_STANDARD_FRAME_FORMAT) {
    can->TXDATA[0] = (tx_msg->ID >> 3);
    can->TXDATA[1] = (tx_msg->ID << 5) | (tx_msg->RTR >> 2);
    data_idx = 2;
  } else { // CAN_EXTENDTED_FRAME_FORMAT
    can->TXDATA[0] = (tx_msg->ID >> 21);
    can->TXDATA[1] = (tx_msg->ID >> 13);
    can->TXDATA[2] = (tx_msg->ID >>  5);
    can->TXDATA[3] = (tx_msg->ID <<  3) | (tx_msg->RTR >> 4);
    data_idx = 4;
  }
  for (unsigned int i = 0; i < tx_msg->DLC; ++i) {
    can->TXDATA[data_idx + i] = tx_msg->Data[i];
  }
}

void CAN_Transmit(CAN_TypeDef *can, CAN_TxMessageTypeDef *tx_msg)
{
  CAN_PrepareTx(can, tx_msg);
  CAN_StartTx(can);
}

void CAN_Receive(CAN_TypeDef *can, CAN_RxMessageTypeDef *rx_msg)
{
  CAN_WaitForRx(can);
  uint32_t rx_frame = can->RXFRAME;
  rx_msg->FF  = rx_frame & CAN_FRAME_FF;
  rx_msg->RTR = rx_frame & CAN_FRAME_RTR;
  rx_msg->DLC = rx_frame & CAN_FRAME_DLC;
  if (rx_msg->RTR == CAN_REMOTE_FRAME) {
    rx_msg->DLC = 0;
  }

  int data_idx;
  if (rx_msg->FF == CAN_STANDARD_FRAME_FORMAT) {
    rx_msg->ID = (can->RXDATA[0] << 3 ) | (can->RXDATA[1] >> 5);
    data_idx = 2;
  } else { // CAN_EXTENDTED_FRAME_FORMAT
    rx_msg->ID = (can->RXDATA[0] << 21) | (can->RXDATA[1] << 13) | (can->RXDATA[2] << 5) | (can->RXDATA[3] >> 3);
    data_idx = 4;
  }
  for (unsigned int i = 0; i < rx_msg->DLC; ++i) {
    rx_msg->Data[i] = can->RXDATA[data_idx + i];
  }
  CAN_ReleaseRxBuffer(can);
}
