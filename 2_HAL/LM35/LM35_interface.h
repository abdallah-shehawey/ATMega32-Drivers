/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LM35_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : LM35
 *
 */
#include "STD_TYPES.h"

#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

#define ADC_RES_10_BIT 0
#define ADC_RES_8_BIT  1

typedef struct
{
  u8 Copy_u8LM35Channel;
  u8 Copy_u8ADCVoltageRefrence; /* Vref = 5, 2.56, External*/
  u8 Copy_u8ADCRes;             /*ADC_RES_10_BIT or ADC_RES_8_BIT*/
} LM35_Config;

u8 LM35_u8GetTemp(LM35_Config * lm35, u8 *Copy_u8TempValue);
u8 LM35_u8GetAnalogSignal(LM35_Config *lm35, u16 *Local_u16AnalogSignal);

#endif /* LM35_INTERFACE_H_ */
