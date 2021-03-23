#ifndef _AGM_CRC_H
#define _AGM_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

typedef struct
{
  __IO uint32_t DR;        // 0x00, CRC Data register
  __IO uint8_t  IDR;       // 0x04, CRC Independent data register
  __IO uint8_t  RESERVED0; // 0x05, Reserved
  __IO uint16_t RESERVED1; // 0x06, Reserved
  __IO uint32_t CR;        // 0x08, CRC Control register
  __IO uint32_t RESERVED2; // 0x0C, Reserved
  __IO uint32_t INIT;      // 0x10, Initial CRC value register
  __IO uint32_t POL;       // 0x14, CRC polynomial register
} CRC_TypeDef;

#define CRC_CR_RESET   (1 << 0)

#define CRC_CR_POLY_OFFSET 3
#define CRC_CR_POLY_MASK   (3 << CRC_CR_POLY_OFFSET)

#define CRC_CR_REV_IN_OFFSET 5
#define CRC_CR_REV_IN_MASK   (3 << CRC_CR_REV_IN_OFFSET)

#define CRC_CR_REV_OUT_OFFSET 7
#define CRC_CR_REV_OUT_MASK   (1 << CRC_CR_REV_OUT_OFFSET)

#define CRC_CR_ENDIAN_OFFSET 8
#define CRC_CR_ENDIAN_MASK   (1 << CRC_CR_ENDIAN_OFFSET)

typedef enum
{
  CRC_CR_POLY32 = 0 << CRC_CR_POLY_OFFSET,
  CRC_CR_POLY16 = 1 << CRC_CR_POLY_OFFSET,
  CRC_CR_POLY8  = 2 << CRC_CR_POLY_OFFSET,
  CRC_CR_POLY7  = 3 << CRC_CR_POLY_OFFSET,
} CRC_PolySizeTypeDef;

typedef enum
{
  CRC_CR_REV_IN_NONE  = 0 << CRC_CR_REV_IN_OFFSET,
  CRC_CR_REV_IN_BYTE  = 1 << CRC_CR_REV_IN_OFFSET,
  CRC_CR_REV_IN_HWORD = 2 << CRC_CR_REV_IN_OFFSET,
  CRC_CR_REV_IN_WORD  = 3 << CRC_CR_REV_IN_OFFSET,
} CRC_ReverseInputTypeDef;

typedef enum
{
  CRC_CR_REV_OUT_NONE = 0 << CRC_CR_REV_OUT_OFFSET,
  CRC_CR_REV_OUT_BIT  = 1 << CRC_CR_REV_OUT_OFFSET,
} CRC_ReverseOutputTypeDef;

typedef enum
{
  CRC_CR_BIG_ENDIAN    = 0 << CRC_CR_ENDIAN_OFFSET,
  CRC_CR_LITTLE_ENDIAN = 1 << CRC_CR_ENDIAN_OFFSET,
} CRC_EndianTypeDef;

void CrcInit(uint32_t init, uint32_t poly);
void CrcUpdate(uint32_t bits, uint8_t l);

// Reset the CRC unit and calculation will restart from value in crc->INIT. But the read value of crc->DR will hold the 
// previous calculation result. After any new data is fed, read value of DR will reflect the new calculation result.
static inline void CRC_Reset(CRC_TypeDef *crc) { crc->CR = CRC_CR_RESET; }
static inline void CRC_ResetData(CRC_TypeDef *crc) { crc->CR |= CRC_CR_RESET; }

static inline void CRC_SetPolySize(CRC_TypeDef *crc, CRC_PolySizeTypeDef poly_size)
{
  MODIFY_REG(crc->CR, CRC_CR_POLY_MASK, poly_size);
}

static inline void CRC_SetReverseInput(CRC_TypeDef *crc, CRC_ReverseInputTypeDef rev_in)
{
  MODIFY_REG(crc->CR, CRC_CR_REV_IN_MASK, rev_in);
}

static inline void CRC_SetOutputDataReverseMode(CRC_TypeDef *crc, CRC_ReverseOutputTypeDef rev_out)
{
  MODIFY_REG(crc->CR, CRC_CR_REV_OUT_MASK, rev_out);
}

static inline void CRC_SetEndian(CRC_TypeDef *crc, CRC_EndianTypeDef endian)
{
  MODIFY_REG(crc->CR, CRC_CR_ENDIAN_MASK, endian);
}

static inline void CRC_SetInitData(CRC_TypeDef *crc, uint32_t init) { crc->INIT = init; }
static inline void CRC_SetPolyCoef(CRC_TypeDef *crc, uint32_t coef) { crc->POL  = coef; }

static inline uint32_t CRC_GetInitData(CRC_TypeDef *crc) { return crc->INIT; }
static inline uint32_t CRC_GetPolyCoef(CRC_TypeDef *crc) { return crc->POL; }

static inline void CRC_FeedData32(CRC_TypeDef *crc, uint32_t data) { crc->DR = data;   }
static inline void CRC_FeedData16(CRC_TypeDef *crc, uint16_t data) { *(__IO uint16_t *)(&crc->DR) = data; }
static inline void CRC_FeedData8 (CRC_TypeDef *crc, uint8_t  data) { *(__IO uint8_t  *)(&crc->DR) = data; }

static inline uint32_t CRC_ReadData32(CRC_TypeDef *crc) { return crc->DR; }
static inline uint16_t CRC_ReadData16(CRC_TypeDef *crc) { return (uint16_t)(crc->DR); }
static inline uint8_t  CRC_ReadData8 (CRC_TypeDef *crc) { return (uint8_t)(crc->DR); }
static inline uint8_t  CRC_ReadData7(CRC_TypeDef *crc)  { return CRC_ReadData8(crc) & 0x7F; }

#ifdef __cplusplus
}
#endif

#endif
