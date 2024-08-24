/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LM35_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : LM35
 *
 */

#include "STD_TYPES.h"
#include "STD_MACROS.h"

#include "DIO_interface.h"
#include "ADC_interface.h"

#include "LM35_interface.h"
#include "LM35_private.h"

/*___________________________________________________________________________________________________________________*/

/*
* Breif : This Function initialize the pin which connected to led as output pin
* Parameters :
            => struct has the LM35 Channel, ADC VoltageReference , ADCResolution
      => Pointer to TEMP Variable which will return in it
* return : Error State
*/
u8 LM35_u8GetTemp(LM35_Config *lm35, u8 *Copy_u8TempValue)
{
  u8 Local_u8ErrorState = OK;

  u16 Local_u16ADCResult;
  u16 Local_u16AnalogSignal;

  u16 Local_u8ADCRefrence = (lm35->Copy_u8ADCVoltageRefrence) * 1000; // to convert from(V --> mV)

  /* ADC Digital Reading */
  ADC_u8GetResultSync(lm35->Copy_u8LM35Channel, &Local_u16ADCResult);

  /* Check for ADC Resolution */
  if (lm35->Copy_u8ADCRes == ADC_RES_10_BIT)
  {
    Local_u16AnalogSignal = (u16)(((u32)Local_u16ADCResult * (u32)Local_u8ADCRefrence) / 1024UL);
  }
  else if (lm35->Copy_u8ADCRes == ADC_RES_8_BIT)
  {
    Local_u16AnalogSignal = (u16)(((u32)Local_u16ADCResult * (u32)Local_u8ADCRefrence) / 256UL);
  }

  /* Convert (mv --> Temp) */
  *Copy_u8TempValue = Local_u16AnalogSignal / 10;

  return Local_u8ErrorState;
}

/*___________________________________________________________________________________________________________________*/

/*
* Breif : This Function used to return analog signal only to return analog signal only
*you can use it to get analog and calc negative temp
* Parameters :
            => struct has the LM35 Channel, ADC VoltageReference , ADCResolution
      => Pointer to TEMP Variable which will return in it
* return : Error State
*/

u8 LM35_u8GetAnalogSignal(LM35_Config *lm35, u16 *Local_u16AnalogSignal)
{
  u8 Local_u8ErrorState = OK;

  u16 Local_u16ADCResult;

  u16 Local_u8ADCRefrence = (lm35->Copy_u8ADCVoltageRefrence) * 1000; // to convert from(V --> mV)

  /* ADC Digital Reading */
  ADC_u8GetResultSync(lm35->Copy_u8LM35Channel, &Local_u16ADCResult);

  /* Check for ADC Resolution */
  if (lm35->Copy_u8ADCRes == ADC_RES_10_BIT)
  {
    *Local_u16AnalogSignal = (u16)(((u32)Local_u16ADCResult * (u32)Local_u8ADCRefrence) / 1024UL);
  }
  else if (lm35->Copy_u8ADCRes == ADC_RES_8_BIT)
  {
    *Local_u16AnalogSignal = (u16)(((u32)Local_u16ADCResult * (u32)Local_u8ADCRefrence) / 256UL);
  }

  return Local_u8ErrorState;
}
