#include "gptimer.h"

void GPTIMER_StructInit(GPTIMER_InitTypeDef *init)
{
  init->Prescaler         = 0;
  init->CounterMode       = GPTIMER_COUNTERMODE_UP;
  init->Autoreload        = -1;
  init->ClockDivision     = GPTIMER_CLOCKDIVISION_DIV1;
  init->RepetitionCounter = 0;
}

ReturnCodeTypedef GPTIMER_Init(GPTIMER_TypeDef *gpt, GPTIMER_InitTypeDef *init)
{
  GPTIMER_SetCounterMode      (gpt, init->CounterMode      );
  GPTIMER_SetClockDivision    (gpt, init->ClockDivision    );
  GPTIMER_SetAutoReload       (gpt, init->Autoreload       );
  GPTIMER_SetPrescaler        (gpt, init->Prescaler        );
  GPTIMER_SetRepetitionCounter(gpt, init->RepetitionCounter);

  GPTIMER_GenerateEventUpdate(gpt);
  return RET_OK;
}

void GPTIMER_OC_StructInit(GPTIMER_OC_InitTypeDef *oc_init)
{
  oc_init->OCMode       = GPTIMER_OCMODE_FROZEN;
  oc_init->OCState      = GPTIMER_OCSTATE_DISABLE;
  oc_init->OCNState     = GPTIMER_OCSTATE_DISABLE;
  oc_init->OCPolarity   = GPTIMER_OC_POLARITY_NONINVERTED;
  oc_init->OCNPolarity  = GPTIMER_OC_POLARITY_NONINVERTED;
  oc_init->OCIdleState  = GPTIMER_OCIDLESTATE_LOW;
  oc_init->OCNIdleState = GPTIMER_OCIDLESTATE_LOW;
  oc_init->CompareValue = 0;
}

void GPTIMER_OC_Init(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_OC_InitTypeDef *oc_init)
{
  GPTIMER_CC_DisableChannel (gpt, channel                       );
  GPTIMER_OC_SetCompare     (gpt, channel, oc_init->CompareValue);
  GPTIMER_OC_SetIdleState   (gpt, channel, oc_init->OCIdleState );
  GPTIMER_OCN_SetIdleState  (gpt, channel, oc_init->OCNIdleState);
  GPTIMER_OC_SetMode        (gpt, channel, oc_init->OCMode      );
  GPTIMER_OC_SetPolarity    (gpt, channel, oc_init->OCPolarity  );
  GPTIMER_OCN_SetPolarity   (gpt, channel, oc_init->OCNPolarity );
  GPTIMER_OC_SetEnableState (gpt, channel, oc_init->OCState, oc_init->OCNState);
}

void GPTIMER_IC_StructInit(GPTIMER_IC_InitTypeDef *ic_init)
{
  ic_init->ICPolarity  = GPTIMER_IC_POLARITY_RISING;
  ic_init->ICMode      = GPTIMER_ICMODE_DIRECTTI;
  ic_init->ICPrescaler = GPTIMER_ICPSC_DIV1;
  ic_init->ICFilter    = GPTIMER_IC_FILTER_FDIV1;
}

void GPTIMER_IC_Init(GPTIMER_TypeDef *gpt, GPTIMER_ChannelNumTypeDef channel, GPTIMER_IC_InitTypeDef *ic_init)
{
  GPTIMER_CC_DisableChannel(gpt, channel                      );
  GPTIMER_IC_SetInputMode  (gpt, channel, ic_init->ICMode     );
  GPTIMER_IC_SetPrescaler  (gpt, channel, ic_init->ICPrescaler);
  GPTIMER_IC_SetFilter     (gpt, channel, ic_init->ICFilter   );
  GPTIMER_IC_SetPolarity   (gpt, channel, ic_init->ICPolarity );
  GPTIMER_CC_EnableChannel (gpt, channel                      );
}

void GPTIMER_ENCODER_StructInit(GPTIMER_ENCODER_InitTypeDef *encoder_init)
{
  encoder_init->EncoderMode  = GPTIMER_ENCODERMODE_X2_TI0;
  encoder_init->IC0Polarity  = GPTIMER_IC_POLARITY_RISING;
  encoder_init->IC0Mode      = GPTIMER_ICMODE_DIRECTTI;
  encoder_init->IC0Prescaler = GPTIMER_ICPSC_DIV1;
  encoder_init->IC0Filter    = GPTIMER_IC_FILTER_FDIV1;
  encoder_init->IC1Polarity  = GPTIMER_IC_POLARITY_RISING;
  encoder_init->IC1Mode      = GPTIMER_ICMODE_DIRECTTI;
  encoder_init->IC1Prescaler = GPTIMER_ICPSC_DIV1;
  encoder_init->IC1Filter    = GPTIMER_IC_FILTER_FDIV1;
}

ReturnCodeTypedef GPTIMER_ENCODER_Init(GPTIMER_TypeDef *gpt, GPTIMER_ENCODER_InitTypeDef *encoder_init)
{
  GPTIMER_CC_DisableChannel(gpt, GPTIMER_CHANNEL_CH0);
  GPTIMER_CC_DisableChannel(gpt, GPTIMER_CHANNEL_CH1);

  GPTIMER_IC_SetInputMode(gpt, GPTIMER_CHANNEL_CH0, encoder_init->IC0Mode     );
  GPTIMER_IC_SetPrescaler(gpt, GPTIMER_CHANNEL_CH0, encoder_init->IC0Prescaler);
  GPTIMER_IC_SetFilter   (gpt, GPTIMER_CHANNEL_CH0, encoder_init->IC0Filter   );
  GPTIMER_IC_SetPolarity (gpt, GPTIMER_CHANNEL_CH0, encoder_init->IC0Polarity );
  GPTIMER_IC_SetInputMode(gpt, GPTIMER_CHANNEL_CH1, encoder_init->IC1Mode     );
  GPTIMER_IC_SetPrescaler(gpt, GPTIMER_CHANNEL_CH1, encoder_init->IC1Prescaler);
  GPTIMER_IC_SetFilter   (gpt, GPTIMER_CHANNEL_CH1, encoder_init->IC1Filter   );
  GPTIMER_IC_SetPolarity (gpt, GPTIMER_CHANNEL_CH1, encoder_init->IC1Polarity );

  GPTIMER_SetEncoderMode(gpt, encoder_init->EncoderMode);
  gpt->CCER |= (GPTIMER_CCER_CC0E | GPTIMER_CCER_CC1E);

  return RET_OK;
}

void GPTIMER_HALLSENSOR_StructInit(GPTIMER_HALLSENSOR_InitTypeDef *hall_init)
{
  hall_init->IC0Polarity      = GPTIMER_IC_POLARITY_RISING;
  hall_init->IC0Prescaler     = GPTIMER_ICPSC_DIV1;
  hall_init->IC0Filter        = GPTIMER_IC_FILTER_FDIV1;
  hall_init->CommutationDelay = 0;
}

ReturnCodeTypedef GPTIMER_HALLSENSOR_Init(GPTIMER_TypeDef *gpt, GPTIMER_HALLSENSOR_InitTypeDef *hall_init)
{
  GPTIMER_CC_DisableChannel(gpt, GPTIMER_CHANNEL_CH0);
  GPTIMER_CC_DisableChannel(gpt, GPTIMER_CHANNEL_CH1);

  GPTIMER_SetSlaveMode    (gpt, GPTIMER_SLAVEMODE_RESET);
  GPTIMER_SetTriggerInput (gpt, GPTIMER_TS_TI0F_ED     );
  GPTIMER_SetTriggerOutput(gpt, GPTIMER_TRGO_OC1REF    );

  GPTIMER_IC_EnableXORCombination(gpt                                              );
  GPTIMER_IC_SetInputMode        (gpt, GPTIMER_CHANNEL_CH0, GPTIMER_ICMODE_TRC     );
  GPTIMER_IC_SetPrescaler        (gpt, GPTIMER_CHANNEL_CH0, hall_init->IC0Prescaler);
  GPTIMER_IC_SetFilter           (gpt, GPTIMER_CHANNEL_CH0, hall_init->IC0Filter   );
  GPTIMER_IC_SetPolarity         (gpt, GPTIMER_CHANNEL_CH0, hall_init->IC0Polarity );

  GPTIMER_OC_DisableFast   (gpt, GPTIMER_CHANNEL_CH1                             );
  GPTIMER_OC_DisablePreload(gpt, GPTIMER_CHANNEL_CH1                             );
  GPTIMER_OC_DisableClear  (gpt, GPTIMER_CHANNEL_CH1                             );
  GPTIMER_OC_SetMode       (gpt, GPTIMER_CHANNEL_CH1, GPTIMER_OCMODE_PWM2        );
  GPTIMER_OC_SetCompare    (gpt, GPTIMER_CHANNEL_CH1, hall_init->CommutationDelay);

  gpt->CCER |= (GPTIMER_CCER_CC0E | GPTIMER_CCER_CC1E);
  return RET_OK;
}

void GPTIMER_BDTR_StructInit(GPTIMER_BDTR_InitTypeDef *bdtr_init)
{
  bdtr_init->OSSIState         = GPTIMER_OSSI_DISABLE;
  bdtr_init->OSSRState         = GPTIMER_OSSR_DISABLE;
  bdtr_init->LockLevel         = GPTIMER_LOCKLEVEL_OFF;
  bdtr_init->BreakState        = GPTIMER_BREAK_DISABLE;
  bdtr_init->BreakPolarity     = GPTIMER_BREAK_POLARITY_LOW;
  bdtr_init->BreakFilter       = GPTIMER_BREAK_FILTER_FDIV1;
  bdtr_init->AutomaticOutput   = GPTIMER_AUTOMATICOUTPUT_DISABLE;
  bdtr_init->DeadTimeGenerator = 0;
}

ReturnCodeTypedef GPTIMER_BDTR_Init(GPTIMER_TypeDef *gpt, GPTIMER_BDTR_InitTypeDef *bdtr_init)
{
  // Lock level can only be written on the first write to BDCR.
  uint32_t bdtr = bdtr_init->AutomaticOutput | bdtr_init->BreakPolarity | bdtr_init->BreakState |
    bdtr_init->OSSRState | bdtr_init->OSSIState | bdtr_init->LockLevel | bdtr_init->DeadTimeGenerator;
  if (bdtr_init->AutomaticOutput == GPTIMER_AUTOMATICOUTPUT_ENABLE) {
    bdtr |= GPTIMER_BDTR_MOE;
  }
  gpt->BDTR = bdtr;
  return RET_OK;
}
