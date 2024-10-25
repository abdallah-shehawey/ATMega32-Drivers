#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_

#include "STD_TYPES.h"

#define ADC_RES_10_BIT 0
#define ADC_RES_8_BIT  1

typedef struct
{
  u8 Copy_u8LDRChannel            ;
  u8 Copy_u8ADCVoltageRefrence     ; /* Vref = 5, 2.56, External*/
  u8 Copy_u8ADCRes                 ; /*ADC_RES_10_BIT or ADC_RES_8_BIT*/
} LDR_Config;

u8 LDR_u8GetLightPres                  (LDR_Config * LDR, u8 *Copy_u8LightPres     );

#endif /* LDR_INTERFACE_H_ */
