#include "usb.h"

void USB_Reset(void)
{
  USB->USBCMD |= USB_CMD_RST;
  while (USB->USBCMD & USB_CMD_RST);
}

void USB_InitDevice(void)
{
  USB_Reset();
  USB_SetControllerMode(USB_MODE_DEIVCE);
  USB_SetInt(USB_INT_SLI | USB_INT_URI | USB_INT_SEI | USB_INT_PCI | USB_INT_UEI | USB_INT_UI);
  USB_Run();
}

void USB_BusReset(void)
{
  USB_SetEndPtNakEN(0);
  USB_ClearEndPtSetupStatus(USB_GetEndPtSetupStatus());
  USB_ClearEndPtComplete(USB_GetEndPtComplete());
  USB_ClearEndPtNak(USB_GetEndPtNak());
  USB_ClearStatus(USB_GetStatus());

  while (USB_GetEndPtPrime());
  USB_SetEndPtFlush(-1);
  while (USB_GetEndPtFlush());
  USB_PortWaitForReset();
}

void USB_InitDTD(USB_DTD *dTD, void *data_buffer, uint16_t total_bytes)
{
  dTD->Next       = USB_TERMINATE;
  dTD->Status     = 0;
  dTD->Active     = 1;
  dTD->TotalBytes = dTD->ExpectedBytes = total_bytes;

  dTD->BufferPointer[0] = (uint32_t)data_buffer;
  for(uint8_t i = 1; i < 5; ++i) {
    dTD->BufferPointer[i] = (((uint32_t)data_buffer >> 12) + i) << 12;
  }
}

void USB_InitDQH(USB_DQH *dQH)
{
  memset(dQH, 0, sizeof(USB_DQH));
  dQH->ZeroLengthTerminationDisable = true;
  dQH->MaxPacketLength              = USB_MAX_PACKET_LEN;
  dQH->Overlay.Next                 = USB_TERMINATE;
}


void USB_InitHost(void)
{
  USB_Reset();
  USB_SetControllerMode(USB_MODE_HOST);
  USB_SetInt(USB_INT_UPI | USB_INT_UAI | USB_INT_AAI | USB_INT_SEI | USB_INT_FRI | USB_INT_PCI | USB_INT_UEI | USB_INT_UI);
  USB_Run();
}

void USB_InitQTD(USB_QTD *qTD, void *data_buffer, uint16_t total_bytes, USB_PID_TypeDef pid)
{
  qTD->Next.Address    = USB_TERMINATE;
  qTD->AltNext.Address = USB_TERMINATE;
  qTD->Status          = 0;
  qTD->TotalBytes      = total_bytes;
  qTD->PID             = pid;
  qTD->Active          = 1;

  qTD->BufferPointer[0] = (uint32_t)data_buffer;
  for(uint8_t i = 1; i < 5; ++i) {
    qTD->BufferPointer[i] = (((uint32_t)data_buffer >> 12) + i) << 12;
  }
}

void USB_SetQueueHeadLinkPointer(USB_QHD *qHD, USB_QHD *next)
{
  qHD->LinkPointer.Address = (uint32_t)next;
  qHD->LinkPointer.Type = USB_LP_TYP_QH;
}

void USB_InitQHD(USB_QHD *qHD, uint8_t ep, uint8_t addr, USB_LinkPointerItemTypeDef type)
{
  memset(qHD, 0, sizeof(USB_QHD));

  qHD->DeviceAddr      = addr;
  qHD->EndPtNumber     = ep;
  qHD->EndPtSpeed      = USB_FS ? USB_FULL_SPEED : USB_HIGH_SPEED;
  qHD->MaxPacketLength = USB_MAX_PACKET_LEN;
  qHD->Mult            = 1;

  if (ep == USB_SETUP_EP) {
    qHD->DataToggleControl = 1;
    qHD->HeadList = 1;
    qHD->ControlEndPt = (qHD->EndPtSpeed != USB_HIGH_SPEED);
    qHD->LinkPointer.Address = (uint32_t)qHD;
    qHD->LinkPointer.Type = type;
  }
}
