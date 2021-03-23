#ifndef _AGM_USB_H
#define _AGM_USB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

#define USB USB0 // This is the only USB supported for now
#define USB_ENDPOINTS 4
#define USB_FS 1
#define USB_MAX_PACKET_LEN (USB_FS ? 0x40 : 0x200)

typedef struct 
{
  __IO uint32_t Reserved0[32];            // 0x000h-0x07Ch, Reserved
  __IO uint32_t GPTIMER0LD;               // 0x080h, GPTIMER0LD General Purpose Timer #0 Load Register
  __IO uint32_t GPTIMER0CTRL;             // 0x084h, GPTIMER0CTRL General Purpose Timer #0 Control Register
  __IO uint32_t GPTIMER1LD;               // 0x088h, GPTIMER1LD General Purpose Timer #1 Load Register
  __IO uint32_t GPTIMER1CTRL;             // 0x08Ch, GPTIMER1CTRL General Purpose Timer #1 Control Register
  __IO uint32_t Reserved1[28];            // 0x090h-0x0FCh, Reserved
  __I  uint8_t  CAPLENGTH;                // 0x100h, CAPLENGTH Capability Register Length
  __IO uint8_t  Reserved2;                // 0x101h, Reserved
  __I  uint16_t HCIVERSION;               // 0x102h, HCIVERSION Host Interface Version Number
  __I  uint32_t HCSPARAMS;                // 0x104h, HCSPARAMS Host Ctrl. Structural Parameters
  __I  uint32_t HCCPARAMS;                // 0x108h, HCCPARAMS Host Ctrl. Capability Parameters
  __IO uint32_t Reserved3[13];            // 0x10Ch-0x13Ch, Reserved
  __IO uint32_t USBCMD;                   // 0x140h, USB Command
  __IO uint32_t USBSTS;                   // 0x144h, USB Status
  __IO uint32_t USBINTR;                  // 0x148h, USB Interrupt Enable
  __IO uint32_t FRINDEX;                  // 0x14Ch, USB Frame Index
  __IO uint32_t Reserved4;                // 0x150h, Reserved
  union {
    __IO uint32_t PERIODICLISTBASE;       // 0x154h, Frame List Base Address
    __IO uint32_t DEVICEADDR;             // 0x154h, Device Address
  };
  union {
    __IO uint32_t ASYNCLISTADDR;          // 0x158h, Next Asynchronous List Address
    __IO uint32_t ENDPOINTLISTADDR;       // 0x158h, Next Asynchronous List Address
  };
  __IO uint32_t Reserved5;                // 0x15Ch, Reserved
  __IO uint32_t BURSTSIZE;                // 0x160h, Programmable Burst Size
  __IO uint32_t TXFILLTUNING;             // 0x164h, Host Transmit Pre-Buffer Packet Tuning
  __IO uint32_t Reserved6[4];             // 0x168h-0x174h, Reserved
  __IO uint32_t ENDPTNAK;                 // 0x178h, Endpoint NAK
  __IO uint32_t ENDPTNAKEN;               // 0x17Ch, Endpoint NAK Enable
  __IO uint32_t CONFIGFLAG;               // 0x180h, Configured Flag Register
  __IO uint32_t PORTSC;                   // 0x184h, Port Status/Control
  __IO uint32_t Reserved7[7];             // 0x188h-0x1A0h, Reserved
  __IO uint32_t OTGSC;                    // 0x1A4h, OTG Status and Control
  __IO uint32_t USBMODE;                  // 0x1A8h, USB Device Mode
  __IO uint32_t ENDPTSETUPSTAT;           // 0x1ACh, Endpoint Setup Status
  __IO uint32_t ENDPTPRIME;               // 0x1B0h, Endpoint Initialization
  __IO uint32_t ENDPTFLUSH;               // 0x1B4h, Endpoint De-Initialize
  __I  uint32_t ENDPTSTATUS;              // 0x1B8h, Endpoint Status
  __IO uint32_t ENDPTCOMPLETE;            // 0x1BCh, Endpoint Complete
  __IO uint32_t ENDPTCTRL[USB_ENDPOINTS]; // 0x1C0h, Endpoint Control
} USB_TypeDef;

#define USB_CMD_ITC_OFFSET 16

#define USB_CMD_RS    (1 << 0)  // Run/Stop
#define USB_CMD_RST   (1 << 1)  // Controller Reset
#define USB_CMD_FS0   (1 << 2)  // Periodic Schedule Enable Bit 0
#define USB_CMD_FS1   (1 << 3)  // Periodic Schedule Enable Bit 1
#define USB_CMD_PSE   (1 << 4)  // Periodic Schedule Enable
#define USB_CMD_ASE   (1 << 5)  // Asynchronous Schedule Enable
#define USB_CMD_IAA   (1 << 6)  // Interrupt on Async Advance Doorbell
#define USB_CMD_SUTW  (1 << 13) // Setup TripWire
#define USB_CMD_ATDTW (1 << 14) // Add dTD TripWire
#define USB_CMD_FS2   (1 << 15) // Periodic Schedule Enable Bit 2
#define USB_CMD_ITC   (0xff << USB_CMD_ITC_OFFSET) // Interrupt Threshold Control

#define USB_INT_UI    (1 << 0)  // USB Interrupt (completion of a TD)
#define USB_INT_UEI   (1 << 1)  // USB Error Interrupt
#define USB_INT_PCI   (1 << 2)  // Port Change Detect
#define USB_INT_FRI   (1 << 3)  // Frame List Rollover
#define USB_INT_SEI   (1 << 4)  // System Error (from AHB)
#define USB_INT_AAI   (1 << 5)  // Interrupt on Async Advance
#define USB_INT_URI   (1 << 6)  // USB Reset Received
#define USB_INT_SRI   (1 << 7)  // SOF Received
#define USB_INT_SLI   (1 << 8)  // DCSuspend
#define USB_INT_HCH   (1 << 12) // HCHalted
#define USB_INT_RCL   (1 << 13) // Reclamation
#define USB_INT_PS    (1 << 14) // Periodic Schedule Status
#define USB_INT_AS    (1 << 15) // Asynchronous Schedule Status
#define USB_INT_NAKI  (1 << 16) // NAK Interrupt
#define USB_INT_UAI   (1 << 18) // USB Host Asynchronous Interrupt
#define USB_INT_UPI   (1 << 19) // USB Host Periodic Interrupt
#define USB_INT_TI0   (1 << 24) // General Purpose Timer Interrupt 0
#define USB_INT_TI1   (1 << 25) // General Purpose Timer Interrupt 1

#define USB_OTGSC_HAAR (1 << 2)  // Hardware Assist Auto-Reset
#define USB_OTGSC_DP   (1 << 4)  // Data Pulsing
#define USB_OTGSC_HADP (1 << 6)  // Hardware Assist Data-Pulse
#define USB_OTGSC_ID   (1 << 8)  // USB ID, 0: A-device, 1: B-device
#define USB_OTGSC_AVV  (1 << 9)  // A VBus Valid
#define USB_OTGSC_ASV  (1 << 10) // A Session Valid
#define USB_OTGSC_BSV  (1 << 11) // B Session Valid
#define USB_OTGSC_BSE  (1 << 12) // B Session End
#define USB_OTGSC_1msT (1 << 13) // 1 millisecond timer toggle
#define USB_OTGSC_DPS  (1 << 14) // Data Bus Pulsing Status
#define USB_OTGSC_IDIS (1 << 16) // USB ID Interrupt Status
#define USB_OTGSC_1msS (1 << 21) // 1 millisecond timer Interrupt Status
#define USB_OTGSC_DPIS (1 << 22) // Data Pulse Interrupt Status
#define USB_OTGSC_IDIE (1 << 24) // USB ID Interrupt Enable
#define USB_OTGSC_1msE (1 << 29) // 1 millisecond timer Interrupt Enable
#define USB_OTGSC_DPIE (1 << 30) // Data Pulse Interrupt Enable

#define USB_MODE_CM   (3 << 0) // Controller Mode
#define USB_MODE_SLOM (1 << 3) // Setup Lockout Mode

#define USB_PORTSC_LS_OFFSET   10
#define USB_PORTSC_PIC_OFFSET  14
#define USB_PORTSC_PSPD_OFFSET 26

#define USB_PORTSC_CCS  (1 << 0)                      // Current Connect Status
#define USB_PORTSC_CSC  (1 << 1)                      // Connect Status Change
#define USB_PORTSC_PE   (1 << 2)                      // Port Enabled
#define USB_PORTSC_PEC  (1 << 3)                      // Port Enabled Change
#define USB_PORTSC_OCA  (1 << 4)                      // Over-current Active
#define USB_PORTSC_OCC  (1 << 5)                      // Over-current Change
#define USB_PORTSC_FPR  (1 << 6)                      // Force Port Resume
#define USB_PORTSC_SUSP (1 << 7)                      // Suspend
#define USB_PORTSC_PR   (1 << 8)                      // Port Reset
#define USB_PORTSC_HSP  (1 << 9)                      // High-Speed Port
#define USB_PORTSC_LS   (3 << USB_PORTSC_LS_OFFSET)   // Line Status, 0: SE0, 1: J-state, 2: K-state
#define USB_PORTSC_PP   (1 << 12)                     // Port Power
#define USB_PORTSC_PO   (1 << 13)                     // Port Owner
#define USB_PORTSC_PIC  (3 << USB_PORTSC_PIC_OFFSET)  // Port Indicator Control, 0:Off, 1: Amber, 2: Green
#define USB_PORTSC_WKCN (1 << 20)                     // Wake on Connect Enable
#define USB_PORTSC_WKDS (1 << 21)                     // Wake on Disconnect Enable
#define USB_PORTSC_WKOC (1 << 22)                     // Wake on Over-current Enable
#define USB_PORTSC_PHCD (1 << 23)                     // PHY Low Power Clock Disable
#define USB_PORTSC_PFSC (1 << 24)                     // Port Force Full Speed Connect
#define USB_PORTSC_PSPD (3 << USB_PORTSC_PSPD_OFFSET) // Port Speed, 0: Full Speed, 1: Low Speed, 2: High Speed, 3: Not Connected

#define USB_ENDPTCTRL_RXT_OFFSET 2
#define USB_ENDPTCTRL_TXT_OFFSET 18

#define USB_ENDPTCTRL_RXS (1 << 0)                        // RX Endpoint Stall
#define USB_ENDPTCTRL_RXT (3 << USB_ENDPTCTRL_RXT_OFFSET) // RX Endpoint Type
#define USB_ENDPTCTRL_RXI (1 << 5)                        // RX Data Toggle Inhibit
#define USB_ENDPTCTRL_RXR (1 << 6)                        // RX Data Toggle Reset
#define USB_ENDPTCTRL_RXE (1 << 7)                        // RX Endpoint Enable
#define USB_ENDPTCTRL_TXS (1 << 16)                       // TX Endpoint Stall
#define USB_ENDPTCTRL_TXT (3 << USB_ENDPTCTRL_TXT_OFFSET) // TX Endpoint Type
#define USB_ENDPTCTRL_TXI (1 << 21)                       // TX Data Toggle Inhibit
#define USB_ENDPTCTRL_TXR (1 << 22)                       // TX Data Toggle Reset
#define USB_ENDPTCTRL_TXE (1 << 23)                       // TX Endpoint Enable

#define USB_ENDPTCTRL_STALL (1 << 0) // Endpoint Stall
#define USB_ENDPTCTRL_TYPE  (3 << 2) // Endpoint Type
#define USB_ENDPTCTRL_DTR   (1 << 6) // Data Toggle Reset
#define USB_ENDPTCTRL_EN    (1 << 7) // Endpoint Enable

typedef enum
{
  USB_FRAME_LIST_1024 = 0,                                       // 4096 bytes
  USB_FRAME_LIST_512  = USB_CMD_FS0,                             // 2048 bytes
  USB_FRAME_LIST_256  = USB_CMD_FS1,                             // 1024 bytes
  USB_FRAME_LIST_128  = USB_CMD_FS1 | USB_CMD_FS0,               // 512 bytes
  USB_FRAME_LIST_64   = USB_CMD_FS2,                             // 256 bytes
  USB_FRAME_LIST_32   = USB_CMD_FS2 | USB_CMD_FS0,               // 128 bytes
  USB_FRAME_LIST_16   = USB_CMD_FS2 | USB_CMD_FS1,               // 64  bytes
  USB_FRAME_LIST_8    = USB_CMD_FS2 | USB_CMD_FS1 | USB_CMD_FS0, // 32  bytes
} USB_FrameListSizeTypeDef;

typedef enum
{
  USB_INT_THRESHOLD0  = 0x00 << USB_CMD_ITC_OFFSET,
  USB_INT_THRESHOLD1  = 0x01 << USB_CMD_ITC_OFFSET,
  USB_INT_THRESHOLD2  = 0x02 << USB_CMD_ITC_OFFSET,
  USB_INT_THRESHOLD4  = 0x04 << USB_CMD_ITC_OFFSET,
  USB_INT_THRESHOLD8  = 0x08 << USB_CMD_ITC_OFFSET,
  USB_INT_THRESHOLD16 = 0x10 << USB_CMD_ITC_OFFSET,
  USB_INT_THRESHOLD32 = 0x20 << USB_CMD_ITC_OFFSET,
  USB_INT_THRESHOLD64 = 0x40 << USB_CMD_ITC_OFFSET,
} USB_IntThresholdTypeDef;

typedef enum
{
  USB_FULL_SPEED = 0,
  USB_LOW_SPEED  = 1,
  USB_HIGH_SPEED = 2,
} USB_SpeedTypeDef;

typedef enum
{
  USB_MODE_IDLE   = 0x0,
  USB_MODE_DEIVCE = 0x2,
  USB_MODE_HOST   = 0x3,
} USB_ControllerModeTypeDef;

typedef enum
{
  USB_ENDPT_DIR_RX = 0,
  USB_ENDPT_DIR_TX = 1,
} USB_EndPtDirTypeDef;

typedef enum
{
  USB_ENDPT_TYPE_CTRL = 0 << 2,
  USB_ENDPT_TYPE_ISO  = 1 << 2,
  USB_ENDPT_TYPE_BULK = 2 << 2,
  USB_ENDPT_TYPE_INT  = 3 << 2,
} USB_EndPtTypeDef;

static inline void USB_Run(void)  { USB->USBCMD |=  USB_CMD_RS; }
static inline void USB_Stop(void) { USB->USBCMD &= ~USB_CMD_RS; }

static inline void USB_EnableAsyncSchedule(void)  { USB->USBCMD |=  USB_CMD_ASE; }
static inline void USB_DisableAsyncSchedule(void) { USB->USBCMD &= ~USB_CMD_ASE; }

static inline void USB_SetFrameListSize(USB_FrameListSizeTypeDef size) { MODIFY_REG(USB->USBCMD, USB_CMD_FS2 | USB_CMD_FS1 | USB_CMD_FS0, size); }
static inline void USB_SetIntThreshold(USB_IntThresholdTypeDef threshold) { MODIFY_REG(USB->USBCMD, USB_CMD_ITC, threshold); }

static inline uint32_t USB_GetStatus(void) { return USB->USBSTS; }
static inline void USB_ClearStatus(uint32_t bits) { USB->USBSTS = bits; }

static inline void USB_SetInt    (uint32_t bits) { USB->USBINTR  =  bits; }
static inline void USB_EnableInt (uint32_t bits) { USB->USBINTR |=  bits; }
static inline void USB_DisableInt(uint32_t bits) { USB->USBINTR &= ~bits; }
static inline bool USB_IsEnabledInt(uint32_t bits) { return USB->USBINTR & bits; }
static inline uint32_t USB_GetEnabledInt(void) { return USB->USBINTR; }

static inline void USB_SetPeriodicListBase(uint32_t base) { USB->PERIODICLISTBASE = base; }

static inline void USB_SetDeviceAddress(uint8_t addr) { USB->DEVICEADDR = addr << 25 | 1 << 24; }
static inline uint8_t USB_GetDeviceAddress(void) { return (USB->DEVICEADDR >> 25) & 0x0f; }

static inline void USB_SetAsyncListAddr(uint32_t addr) { USB->ASYNCLISTADDR = addr; }
static inline uint32_t USB_GetAsyncListAddr(void) { return USB->ASYNCLISTADDR; }

static inline void USB_SetEndPointListAddr(uint32_t addr) { USB->ENDPOINTLISTADDR = addr; }

static inline bool USB_PortIsConnected(void)           { return USB->PORTSC & USB_PORTSC_CCS;  }
static inline bool USB_PortIsConnectStatusChange(void) { return USB->PORTSC & USB_PORTSC_CSC;  }
static inline bool USB_PortIsSuspended(void)           { return USB->PORTSC & USB_PORTSC_SUSP; }

static inline void USB_PortReset(void)              { MODIFY_REG(USB->PORTSC, USB_PORTSC_PE, USB_PORTSC_PR); }
static inline void USB_PortEnablePower(void)        { USB->PORTSC |= USB_PORTSC_PP;   }
static inline void USB_PortClearConnectStatus(void) { USB->PORTSC |= USB_PORTSC_CSC;  }
static inline void USB_PortForceResume(void)        { USB->PORTSC |= USB_PORTSC_FPR;  }
static inline void USB_PortForceFullSpeed(void)     { USB->PORTSC |= USB_PORTSC_PFSC; } 

static inline USB_SpeedTypeDef USB_PortGetSpeed(void) { return (USB_SpeedTypeDef)((USB->PORTSC & USB_PORTSC_PSPD) >> USB_PORTSC_PSPD_OFFSET); }
static inline void USB_PortWaitForReset(void) { while (USB->PORTSC & USB_PORTSC_PR); }

static inline bool USB_OtgIsDevice(void) { return USB->OTGSC & USB_OTGSC_ID; }
static inline bool USB_OtgIsHost  (void) { return !USB_OtgIsDevice();        }

static inline void USB_OtgClearIDStatus(void) { USB->OTGSC |= USB_OTGSC_IDIS; }
static inline void USB_OtgEnableIntID(void)   { USB->OTGSC |= USB_OTGSC_IDIE; }
static inline void USB_OtgAutoReset(void)     { USB->OTGSC |= (USB_OTGSC_HAAR | USB_OTGSC_HADP); } // Hardware assisted auto reset and data pulse

static inline void USB_OtgWaitForDataPulse(void) { while (USB->OTGSC & USB_OTGSC_DPS); }

static inline void USB_SetControllerMode(USB_ControllerModeTypeDef mode) { MODIFY_REG(USB->USBMODE, USB_MODE_CM, mode); }
static inline USB_ControllerModeTypeDef USB_GetControllerMode(void) { return (USB_ControllerModeTypeDef)(USB->USBMODE & USB_MODE_CM); }

static inline void USB_DisableSetupLockout(void) { USB->USBMODE |=  USB_MODE_SLOM; }
static inline void USB_EnableSetupLockout(void)  { USB->USBMODE &= ~USB_MODE_SLOM; }

static inline uint32_t USB_GetEndPtNak(void)         { return USB->ENDPTNAK;       }
static inline uint32_t USB_GetEndPtSetupStatus(void) { return USB->ENDPTSETUPSTAT; }
static inline uint32_t USB_GetEndPtPrime(void)       { return USB->ENDPTPRIME;     }
static inline uint32_t USB_GetEndPtFlush(void)       { return USB->ENDPTFLUSH;     }
static inline uint32_t USB_GetEndPtStatus(void)      { return USB->ENDPTSTATUS;    }
static inline uint32_t USB_GetEndPtComplete(void)    { return USB->ENDPTCOMPLETE;  }

static inline void USB_SetEndPtNakEN(uint32_t bits) { USB->ENDPTNAKEN = bits; }
static inline void USB_SetEndPtPrime(uint32_t bits) { USB->ENDPTPRIME = bits; } // Auto cleared by hardware
static inline void USB_SetEndPtFlush(uint32_t bits) { USB->ENDPTFLUSH = bits; } // Auto cleared by hardware

static inline void USB_ClearEndPtNak        (uint32_t bits) { USB->ENDPTNAK       = bits; }
static inline void USB_ClearEndPtSetupStatus(uint32_t bits) { USB->ENDPTSETUPSTAT = bits; }
static inline void USB_ClearEndPtComplete   (uint32_t bits) { USB->ENDPTCOMPLETE  = bits; }

#define USB_ENDPT_OFFSET(__dir) (__dir == USB_ENDPT_DIR_RX ? 0 : 16)

static inline void USB_StallEndPt       (uint8_t ep, USB_EndPtDirTypeDef dir) { USB->ENDPTCTRL[ep] |=  (USB_ENDPTCTRL_STALL << USB_ENDPT_OFFSET(dir)); }
static inline void USB_ClearEndPtStall  (uint8_t ep, USB_EndPtDirTypeDef dir) { USB->ENDPTCTRL[ep] &= ~(USB_ENDPTCTRL_STALL << USB_ENDPT_OFFSET(dir)); }

static inline void USB_EnableEndPt (uint8_t ep, USB_EndPtDirTypeDef dir) { USB->ENDPTCTRL[ep] |=  (USB_ENDPTCTRL_EN << USB_ENDPT_OFFSET(dir)); }
static inline void USB_DisableEndPt(uint8_t ep, USB_EndPtDirTypeDef dir) { USB->ENDPTCTRL[ep] &= ~(USB_ENDPTCTRL_EN << USB_ENDPT_OFFSET(dir)); }

static inline void USB_ResetEndPtDataToggle(uint8_t ep, USB_EndPtDirTypeDef dir) { USB->ENDPTCTRL[ep] |= USB_ENDPTCTRL_DTR << USB_ENDPT_OFFSET(dir); }

static inline void USB_SetEndPtType(uint8_t ep, USB_EndPtDirTypeDef dir, USB_EndPtTypeDef type)
{
  MODIFY_REG(USB->ENDPTCTRL[ep], USB_ENDPTCTRL_TYPE << USB_ENDPT_OFFSET(dir), type << USB_ENDPT_OFFSET(dir));
}

void USB_Reset(void);
void USB_InitDevice(void);
void USB_BusReset(void);

// Device controller driver transfer descriptor
typedef struct
{
  uint32_t Next;             // 0x00h, Next dTD Pointer
  union {
    __IO uint32_t Status;    // 0x04h, Status
    struct {
      __IO uint32_t Reserved0       : 3;
      __IO uint32_t TranError       : 1;
      __IO uint32_t Reserved1       : 1;
      __IO uint32_t DataError       : 1;
      __IO uint32_t Halted          : 1;
      __IO uint32_t Active          : 1;
      __IO uint32_t Reserved2       : 2;
           uint32_t IsoMultOverride : 2;
      __IO uint32_t Reserved3       : 3;
           uint32_t IntOnComplete   : 1;
      __IO uint32_t TotalBytes      : 15;
      __IO uint32_t Reserved4       : 1;
    };
  };
  uint32_t BufferPointer[5]; // 0x08h, Buffer Pointer
  uint16_t ExpectedBytes;    // 0x1Ch, Expected bytes to be transfered
  uint16_t Reserved;
} USB_DTD;

#define USB_SETUP_EP 0
#define USB_TERMINATE 0x1
#define USB_TD_MAX_BYTES 0x4000 // Recommended max bytes to xfer for each TD (16K)

static inline USB_DTD *USB_DTD_GetNext(USB_DTD *dTD) { return (USB_DTD *)(dTD->Next & ~USB_TERMINATE); }
void USB_InitDTD(USB_DTD *dTD, void *data_buffer, uint16_t total_bytes);

typedef union {
  uint32_t Address;
  struct  {
    uint32_t Terminate : 1;
    uint32_t Type      : 2;
  };
} USB_LinkPointerTypeDef;

typedef enum
{
  USB_LP_TYP_ITD  = 0, // isochronous transfer descriptor
  USB_LP_TYP_QH   = 1, // queue head
  USB_LP_TYP_SITD = 2, // split transaction isochronous transfer descriptor
  USB_LP_TYP_FSTN = 3, // Frame Span Traversal Node
} USB_LinkPointerItemTypeDef;

typedef enum
{
  USB_PID_OUT   = 0x0,
  USB_PID_IN    = 0x1,
  USB_PID_SETUP = 0x2,
} USB_PID_TypeDef;

// Device controller driver queue head
typedef struct
{
  union {
    uint32_t Info;              // 0x00h, Endpoint capabilities/characteristics
    struct {
      uint32_t Reserved0                    : 15;
      uint32_t IntOnSetup                   : 1;
      uint32_t MaxPacketLength              : 11;
      uint32_t Reserved1                    : 2;
      uint32_t ZeroLengthTerminationDisable : 1;
      uint32_t Mult                         : 2;
    };
  };
  __IO uint32_t Current;        // 0x04h, Current dTD Pointer
  __IO USB_DTD  Overlay;        // 0x08h, Transfer Overlay
  __IO uint32_t SetupBuffer[2]; // 0x28h, Setup Buffer
  __IO uint32_t Reserved[2];    // 0x30h, Reserved
  USB_DTD *Head;                // 0x38h, dTD Head, can be used to point to the head of dTD linked list
  USB_DTD *Tail;                // 0x3Ch, dTD Tail
} USB_DQH;

void USB_InitDQH(USB_DQH *dQH);

// Host controller driver queue transfer descriptor
typedef struct
{
  USB_LinkPointerTypeDef Next;    // 0x00h, Next qTD Pointer
  USB_LinkPointerTypeDef AltNext; // 0x04h, Alternate Next qTD Pointer
  union {
    volatile uint32_t Status;     // 0x08h, Status
    struct {
      __IO uint32_t PingError     : 1;
      __IO uint32_t SplitState    : 1;
      __IO uint32_t MissedFrame   : 1;
      __IO uint32_t TranError     : 1;
      __IO uint32_t BabbleError   : 1;
      __IO uint32_t DataError     : 1;
      __IO uint32_t Halted        : 1;
      __IO uint32_t Active        : 1;
           uint32_t PID           : 2;
      __IO uint32_t ErrorCounter  : 2;
      __IO uint32_t CurrentPage   : 3;
           uint32_t IntOnComplete : 1;
      __IO uint32_t TotalBytes    : 15;
      __IO uint32_t DataToggle    : 1;
    };
  };
  uint32_t BufferPointer[5];      // 0x0Ch, Buffer Pointer
} USB_QTD;

static inline USB_QTD *USB_QTD_GetNext(USB_QTD *qTD) { return (USB_QTD *)(qTD->Next.Address & ~USB_TERMINATE); }
void USB_InitQTD(USB_QTD *qTD, void *data_buffer, uint16_t total_bytes, USB_PID_TypeDef pid);

#define USB_DATA_TOGGLE_0 0
#define USB_DATA_TOGGLE_1 1

// Host controller driver queue head
typedef struct
{
  USB_LinkPointerTypeDef LinkPointer;   // 0x00h, Queue Head Horizontal Link Pointer
  union {
    uint32_t EndPointChar;              // 0x04h, Endpoint characteristics
    struct {
      uint32_t DeviceAddr         : 7;  // device address
      uint32_t InactivateNextTran : 1;  // Only valid for Periodic with Full/Slow speed
      uint32_t EndPtNumber        : 4;  // EP number
      uint32_t EndPtSpeed         : 2;  // 0: Full, 1: Low, 2: High
      uint32_t DataToggleControl  : 1;  // 0: use DT in qHD, 1: use DT in qTD
      uint32_t HeadList           : 1;  // Head of the reclamation list
      uint32_t MaxPacketLength    : 11; // Max packet length
      uint32_t ControlEndPt       : 1;  // 1 if is Full/Low speed control endpoint
      uint32_t NakReload          : 4;  // NAK Count Reload
    };
  };
  union {
    uint32_t EndPointCap;               // 0x08h, Endpoint capabilities
    struct {
      uint32_t IntScheduleMask     : 8; // Interrupt Schedule Mask
      uint32_t SplitCompletionMask : 8; // Split Completion Mask for Full/Slow speed
      uint32_t HubAddr             : 7; // Hub Address for Full/Slow speed
      uint32_t PortNumber          : 7; // Hub Port for Full/Slow speed
      uint32_t Mult                : 2; // Transaction per micro frame
    };
  };
  __IO uint32_t Current;                // 0x0Ch, Current qTD Pointer 0
  __IO USB_QTD  Overlay;                // 0x10h, Transfer Overlay
  __IO uint32_t Reserved[2];            // 0x30h, Reserved
  USB_QTD *Head;                        // 0x38h, qTD Head, can be used to point to the head of qTD linked list
  USB_QTD *Tail;                        // 0x3Ch, qTD Tail
} USB_QHD;

static inline uint32_t USB_GetLinkPointerAddr(USB_LinkPointerTypeDef *lp) { return lp->Address & ~0x1f; }

void USB_InitHost(void);
void USB_SetQueueHeadLinkPointer(USB_QHD *qHD, USB_QHD *next);
void USB_InitQHD(USB_QHD *qHD, uint8_t ep, uint8_t addr, USB_LinkPointerItemTypeDef type);

#ifdef __cplusplus
}
#endif

#endif
