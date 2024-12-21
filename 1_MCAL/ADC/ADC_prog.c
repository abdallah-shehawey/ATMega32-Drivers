/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */

#include "../../APP_Layer/STD_TYPES.h"
#include "../../APP_Layer/STD_MACROS.h"

#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"

/*Hint : Must include ADC_CONFIG before ADC_PRIVATE*/

//=====================================================================================================================

/*Global pointer to carry the conversion result in the Asynchronous execution*/
static u16 *ADC_pu16AsynchConversionResult = NULL;

/*Global pointer to function to carry the notification function called by ISR*/
static void (*ADC_pvNotificationFunc)(void) = NULL;

/*Global flag for the ADC ISR State*/
static u8 ADC_u8ISRState;

/*Global pointer to carry the chain Channel*/
static u8 *ADC_pu8ChainChannel;

/*Global variable to carry the chain size*/
static u8 ADC_u8ChainSize;

/*Global variable to indicate for the current ADC Chain*/
static u8 ADC_u8Index;

/*Global flag for the ADC Busy State*/
static u8 ADC_u8State = IDLE;

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function Init the ADC ( Prebuild Function)
 *                                            *-----------------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing
 */

void ADC_vInit(void)
{

  /*Select the voltage reference*/
  #ifdef ADC_VREF

    #if ADC_VREF == AREF

      CLR_BIT(ADMUX, ADMUX_REFS0);
      CLR_BIT(ADMUX, ADMUX_REFS1);

    #elif ADC_VREF == AVCC

      SET_BIT(ADMUX, ADMUX_REFS0);
      CLR_BIT(ADMUX, ADMUX_REFS1);

    #elif ADC_VREF == INTERNAL_2_56

      SET_BIT(ADMUX, ADMUX_REFS0);
      SET_BIT(ADMUX, ADMUX_REFS1);

    #else

    #error "Wrong ADC_VREF config"

    #endif

  #endif

  /*Set Left Adjust Result*/
  #ifdef ADC_ADJUSTMENT

    #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT

      CLR_BIT(ADMUX, ADMUX_ADLAR);

    #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT

      SET_BIT(ADMUX, ADMUX_ADLAR);

    #else

    #error "Wrong ADC_ADJUSTMENT config"

    #endif

  #endif

  /*Set Prescaler Value*/
  #ifdef ADC_PRESCALLER

    #if ADC_PRESCALLER <= ADC_PRE_128

      ADCSRA &= 0b11111000;
      ADCSRA |= ADC_PRESCALLER;

    #else

    #error "Wrong ADC_PRESCALLER config"

    #endif

  #endif

  /*Set Trigger Source Value*/
  #ifdef ADC_TRIGGERING_SOURCE

    #if ADC_TRIGGERING_SOURCE <= ADC_SINGLE_CONVERSION

      #if ADC_TRIGGERING_SOURCE == ADC_SINGLE_CONVERSION

        CLR_BIT(ADCSRA, ADCSRA_ADATE);

      #else

        SET_BIT(ADCSRA, ADCSRA_ADATE);
        SFIOR &= 0b00011111;
        SFIOR |= (ADC_TRIGGERING_SOURCE << 5);

      #endif

    #else

      #error "Wrong ADC_TRIGGERING_SOURCE config"

    #endif

  #endif

    /*Enable ADC Peripheral*/
  #ifdef ADC_STATUS

    #if ADC_STATUS == ADC_DIS

      CLR_BIT(ADCSRA, ADCSRA_ADEN);

    #elif ADC_STATUS == ADC_EN

      SET_BIT(ADCSRA, ADCSRA_ADEN);

    #else

      #error "Wrong ADC_STATUS config"

    #endif

  #endif

    /*Enable ADC Interrupt*/
  #ifdef ADC_INT_STATUS

    #if ADC_INT_STATUS == INT_DIS

      CLR_BIT(ADCSRA, ADCSRA_ADIE);

    #elif ADC_INT_STATUS == INT_EN

      SET_BIT(ADCSRA, ADCSRA_ADIE);

    #else

    #error "Wrong INT_STATUS config"

    #endif

  #endif
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the ADC
 *                                              *--------------------------------------*
 * Parameters : Nothing
 * return     : Nothing
 */
void ADC_vEnable(void)
{
  SET_BIT(ADCSRA, ADCSRA_ADEN);
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the ADC
 *                                                *--------------------------------------*
 * Parameters : Nothing
 * return     : Nothing
 */
void ADC_vDisable(void)
{
  CLR_BIT(ADCSRA, ADCSRA_ADEN);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the ADC Interrupt
 *                                               *----------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing
 */
void ADC_vInterruptEnable(void)
{
  SET_BIT(ADCSRA, ADCSRA_ADIE);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the ADC Interrupt
 *                                                *----------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing
 */
void ADC_vInterruptDisable(void)
{
  CLR_BIT(ADCSRA, ADCSRA_ADIE);
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Voltage reference of the ADC using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters :
 *		=>Copy_u8VREF => [AREF , AVCC , INTERNAL_2_56 ]
 *
 * return     : Error status with type u8
 */
u8 ADC_u8VoltageReference(u8 Copy_u8VREF)
{

  u8 Local_u8ErrorState = NOK;
  if ((Copy_u8VREF == AREF) || (Copy_u8VREF == AVCC) || (Copy_u8VREF == INTERNAL_2_56))
  {
    ADMUX &= 0b00111111;
    ADMUX |= (Copy_u8VREF << 6);
    Local_u8ErrorState = OK;
  }

  return Local_u8ErrorState;
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Prescaler of the ADC (CLK) using postbuild configuration
 *                                             *-----------------------------------------------------------------------------------*
 * Parameters :
 *		=>Copy_u8Prescaler => [ADC_PRE_2 , ADC_PRE_4 , ADC_PRE_8 , ADC_PRE_16 , ADC_PRE_32 , ADC_PRE_64 , ADC_PRE_128]
 *
 * return     : Error status with type u8
 */
u8 ADC_u8SetPrescaler(u8 Copy_u8Prescaler)
{

  u8 Local_u8ErrorState = NOK;

  if (Copy_u8Prescaler <= ADC_PRE_128)
  {
    /*Set Prescaler Value*/
    ADCSRA &= 0b11111000;
    ADCSRA |= Copy_u8Prescaler;
    Local_u8ErrorState = OK;
  }

  return Local_u8ErrorState;
}

/*______________________________________________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Adjustment of the ADC using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters :
 *		=>Copy_u8Adjust => [RIGHT_ADJUSTMENT , LEFT_ADJUSTMENT]
 *
 * return     : Error status with type u8
 */
u8 ADC_u8SetAdjustment(u8 Copy_u8Adjust)
{

  u8 Local_u8ErrorState = OK;

  if (Copy_u8Adjust == RIGHT_ADJUSTMENT)
  {
    CLR_BIT(ADMUX, ADMUX_ADLAR);
  }
  else if (Copy_u8Adjust == LEFT_ADJUSTMENT)
  {
    SET_BIT(ADMUX, ADMUX_ADLAR);
  }
  else
  {
    Local_u8ErrorState = NOK;
  }

  return Local_u8ErrorState;
}

/*_____________________________________________________________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Triggering source of the ADC using postbuild configuration
 *                                             *-----------------------------------------------------------------------------------*
 * Parameters :
 *		=>Copy_u8Trigger => [ADC_FREE_RUNNING , ADC_ANALOG_COMPARATOR , ADC_EXTI0 , ADC_TIM0_CTC , ADC_TIM0_OVF , ADC_TIM1_CTC_CHANNEL_B , ADC_TIM1_OVF , ADC_TIM1_ICU]
 *
 * return     : Error status with type u8
 */
u8 ADC_u8SetTriggerSource(u8 Copy_u8Trigger)
{
  u8 Local_u8ErrorState = OK;

  if (Copy_u8Trigger == ADC_SINGLE_CONVERSION)
  {
    CLR_BIT(ADCSRA, ADCSRA_ADATE);
  }
  else if (Copy_u8Trigger <= ADC_TIM1_ICU)
  {
    /*Set Trigger source Value*/
    SET_BIT(ADCSRA, ADCSRA_ADATE);
    SFIOR &= 0b00011111;
    SFIOR |= (ADC_TRIGGERING_SOURCE << 5);
  }
  else
  {
    Local_u8ErrorState = NOK;
  }

  return Local_u8ErrorState;
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the result of the ADC conversoin using synch method
 *                                          *-----------------------------------------------------------------------------------*
 * Parameters :
 *		=>Copy_u8Channel -> ADC channel -> [0...31]
 *      =>Copy_pu16Result -> pointer to u16
 *
 * return     : Error status with type u8
 */
u8 ADC_u8GetResultSync(u8 Copy_u8Channel, u16 *Copy_pu16Result)
{
  u8 Local_u8ErrorState = OK;

  u32 Local_u32TimeOutCounter = 0;

  if (Copy_pu16Result != NULL)
  {
    if (ADC_u8State == IDLE)
    {
      /*ADC is now Busy*/
      ADC_u8State = BUSY;

      /*Set required channel*/
      if (Copy_u8Channel <= ADC_GND)
      {
        ADMUX &= 0b11100000;
        ADMUX |= Copy_u8Channel;
      }

      /*Start Conversion*/
      SET_BIT(ADCSRA, ADCSRA_ADSC);

      /*Waiting until the conversion is complete*/
      while ((READ_BIT(ADCSRA, ADCSRA_ADIF) == 0) && (Local_u32TimeOutCounter < ADC_TIMEOUT))
      {
        Local_u32TimeOutCounter++;
      }
      if (Local_u32TimeOutCounter == ADC_TIMEOUT)
      {
        Local_u8ErrorState = NOK;
      }
      else
      {
        /*Clear the interrupt flag*/
        SET_BIT(ADCSRA, ADCSRA_ADIF);

/*Return Conversion Result*/
#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT

        *Copy_pu16Result = (ADCL | (ADCH << 8));

#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT

        *Copy_pu16Result = (ADCH << 2);

#else

#error "Wrong ADC_ADJUSTMENT config"

#endif
      }

      /*ADC is IDLE*/
      ADC_u8State = IDLE;
    }
    else
    {
      Local_u8ErrorState = BUSY_STATE;
    }
  }
  else
  {
    Local_u8ErrorState = NULL_POINTER;
  }

  return Local_u8ErrorState;
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the result of the ADC conversoin using Asynch method
 *                                          *-----------------------------------------------------------------------------------*
 * Parameters :
 *		=>Copy_u8Channel : ADC channel -> [0...31]
 *      =>Copy_pu16Result: pointer to u16
 *      =>Copy_pvNotificationFunc : poiter to function
 *
 * return     : Error status with type u8
 */
u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel, u16 *Copy_pu16Result, void (*Copy_pvNotificationFunc)(void))
{
  u8 Local_u8ErrorState = OK;

  if ((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
  {
    if (ADC_u8State == IDLE)
    {
      /*ADC is now Busy*/
      ADC_u8State = BUSY;

      /*Set ISR State*/
      ADC_u8ISRState = SINGLE_CHANNEL_ASYNCH;

      /*Initialize the global result pointer*/
      ADC_pu16AsynchConversionResult = Copy_pu16Result;

      /*Initialize the global notification function pointer*/
      ADC_pvNotificationFunc = Copy_pvNotificationFunc;

      /*Set required channel*/
      if (Copy_u8Channel <= ADC_GND)
      {
        ADMUX &= 0b11100000;
        ADMUX |= Copy_u8Channel;
      }

      /*Start Conversion*/
      SET_BIT(ADCSRA, ADCSRA_ADSC);

      /*ADC Conversion Complete Interrupt Enable*/
      SET_BIT(ADCSRA, ADCSRA_ADIE);
    }
    else
    {
      Local_u8ErrorState = BUSY_STATE;
    }
  }
  else
  {
    Local_u8ErrorState = NULL_POINTER;
  }

  return Local_u8ErrorState;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the result of the ADC conversoin using Asynch method
 *                                            *-----------------------------------------------------------------------------------*
 * Parameters :
 *		=>Copy_Chain :struct
 *    		->Channel:Array of u8
 *          ->Result :Array of u16
 *          ->Size   :Size  of Array
 *          ->NotificationFunc:poiter to function
 *
 *
 * return     : Error status with type u8
 */

u8 ADC_u8StartChainAsynch(Chain_t *Copy_Chain)
{
  u8 Local_u8ErrorState = OK;

  if ((Copy_Chain != NULL) && (Copy_Chain->Channel != NULL) && (Copy_Chain->NotificationFunc != NULL) && (Copy_Chain->Result != NULL))
  {
    if (ADC_u8State == IDLE)
    {
      /*ADC is now Busy*/
      ADC_u8State = BUSY;

      /*Set ISR State*/
      ADC_u8ISRState = CHAIN_CHANNEL_ASYNCH;

      /*Assign the ADC data globally*/
      ADC_pu16AsynchConversionResult = Copy_Chain->Result;
      ADC_pu8ChainChannel = Copy_Chain->Channel;
      ADC_u8ChainSize = Copy_Chain->Size;
      ADC_pvNotificationFunc = Copy_Chain->NotificationFunc;

      /*Set Index to first element*/
      ADC_u8Index = 0;

      /*Set required channel*/
      if (ADC_pu8ChainChannel[ADC_u8Index] <= ADC_GND)
      {
        ADMUX &= 0b11100000;
        ADMUX |= ADC_pu8ChainChannel[ADC_u8Index];
      }

      /*Start Conversion*/
      SET_BIT(ADCSRA, ADCSRA_ADSC);

      /*ADC Conversion Complete Interrupt Enable*/
      SET_BIT(ADCSRA, ADCSRA_ADIE);
    }
    else
    {
      Local_u8ErrorState = BUSY_STATE;
    }
  }
  else
  {
    Local_u8ErrorState = NULL_POINTER;
  }
  return Local_u8ErrorState;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

/* ISR for ADC conversion complete */
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
  if (ADC_u8ISRState == SINGLE_CHANNEL_ASYNCH)
  {
/*Return Conversion Result*/
#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT

    *ADC_pu16AsynchConversionResult = (ADCL | (ADCH << 8));

#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT

    *ADC_pu16AsynchConversionResult = (ADCH << 2);

#else

#error "Wrong ADC_ADJUSTMENT config"

#endif

    /*ADC is IDLE*/
    ADC_u8State = IDLE;

    /*Call Notification Function*/
    ADC_pvNotificationFunc();

#if ADC_TRIGGERING_SOURCE == ADC_SINGLE_CONVERSION
    /*Disable the Conversion Complete Interrupt*/
    CLR_BIT(ADCSRA, ADCSRA_ADIE);
#endif
  }


  else if (ADC_u8ISRState == CHAIN_CHANNEL_ASYNCH)
  {
/*Return Conversion Result*/

  #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT

      ADC_pu16AsynchConversionResult[ADC_u8Index] = (ADCL | (ADCH << 8));

  #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT

      ADC_pu16AsynchConversionResult[ADC_u8Index] = (ADCH << 2);

  #else

  #error "Wrong ADC_ADJUSTMENT config"

  #endif

    /*Increment Data index of the chain*/
    ADC_u8Index++;

    if (ADC_u8Index == ADC_u8ChainSize)
    {
      /*ADC is IDLE*/
      ADC_u8State = IDLE;

      /*Call Notification Function*/
      ADC_pvNotificationFunc();

      /*Disable the Conversion Complete Interrupt*/
      CLR_BIT(ADCSRA, ADCSRA_ADIE);
    }
    else
    {
      /*Set required channel*/
      if (ADC_pu8ChainChannel[ADC_u8Index] <= ADC_GND)
      {
        ADMUX &= 0b11100000;
        ADMUX |= ADC_pu8ChainChannel[ADC_u8Index];
      }
      /*Start Conversion*/
      SET_BIT(ADCSRA, ADCSRA_ADSC);
    }
  }
}
