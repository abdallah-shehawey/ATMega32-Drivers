/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXIT_prog.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */

#include "../../APP_Layer/STD_TYPES.h"
#include "../../APP_Layer/STD_MACROS.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

/*
      Global Pointer to Function => Carry The Adress of ISR func in the main
      Hint : I Made an array of pointers to carry EXTI 0,1,2 according to its index
*/
void (*EXTI_CallBack[3]) (void) = {NULL};

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function Init THE EXTI ( Prebuild Function)
 *                                             *-----------------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing
 */
void EXTI_vInit(void)
{
  #ifdef EXTI_LINE

    #if EXTI_LINE == EXTI_LINE0

      #if EXTI_SENSE_MODE == EXTI_LOW_LEVEL

        CLR_BIT(MCUCR, 0);
        CLR_BIT(MCUCR, 1);

      #elif EXTI_SENSE_MODE == EXTI_ON_CHANGE

        SET_BIT(MCUCR, 0);
        CLR_BIT(MCUCR, 1);

      #elif EXTI_SENSE_MODE == EXTI_FALLING_EDGE

        CLR_BIT(MCUCR, 0);
        SET_BIT(MCUCR, 1);

      #elif EXTI_SENSE_MODE == EXTI_RISING_EDGE

        SET_BIT(MCUCR, 0);
        SET_BIT(MCUCR, 1);

      #endif

    #elif EXTI_LINE == EXTI_LINE1

      #if EXTI_SENSE_MODE == EXTI_LOW_LEVEL

        CLR_BIT(MCUCR, 2);
        CLR_BIT(MCUCR, 3);

      #elif EXTI_SENSE_MODE == EXTI_ON_CHANGE

        SET_BIT(MCUCR, 2);
        CLR_BIT(MCUCR, 3);

      #elif EXTI_SENSE_MODE == EXTI_FALLING_EDGE

        CLR_BIT(MCUCR, 2);
        SET_BIT(MCUCR, 3);

      #elif EXTI_SENSE_MODE == EXTI_RISING_EDGE

        SET_BIT(MCUCR, 2);
        SET_BIT(MCUCR, 3);

      #endif

    #elif EXTI_LINE == EXTI_LINE2

      #if EXTI_SENSE_MODE == EXTI_FALLING_EDGE

        CLR_BIT(MCUCSR, 6);

      #elif EXTI_SENSE_MODE == EXTI_RISING_EDGE

        SET_BIT(MCUCSR, 6);

      #endif
    #endif
  #endif
}

/*___________________________________________________________________________________________________________________*/

/*----------------------------------------------------------------------------------------------------------------------------------
 *         	        A function to set the required sense control of the required EINT Line using postbuild configuration
 *                  *----------------------------------------------------------------------------------------------------*
 * Parameters :
 *		Copy_u8SenseMode => [EXTI_LOW_LEVEL,EXTI_ON_CHANGE,EXTI_FALLING_EDGE,EXTI_RISING_EDGE]
 *		Copy_u8Line      => [EXTI_LINEx](x=0..2)
 *
 * return     : Nothing
 */
void EXTI_vSetSignal(u8 Copy_u8SenseMode, u8 Copy_u8Line)
{
  if (Copy_u8Line >= EXTI_LINE0 && Copy_u8Line <= EXTI_LINE1)
  {
    Copy_u8Line = (6 - Copy_u8Line) * -2;

    switch (Copy_u8SenseMode)
    {
    case EXTI_LOW_LEVEL:
      CLR_BIT(MCUCR, Copy_u8Line);
      CLR_BIT(MCUCR, Copy_u8Line + 1);
      break;
    case EXTI_ON_CHANGE:
      SET_BIT(MCUCR, Copy_u8Line);
      CLR_BIT(MCUCR, Copy_u8Line + 1);
      break;
    case EXTI_FALLING_EDGE:
      CLR_BIT(MCUCR, Copy_u8Line);
      SET_BIT(MCUCR, Copy_u8Line + 1);
      break;
    case EXTI_RISING_EDGE:
      SET_BIT(MCUCR, Copy_u8Line);
      SET_BIT(MCUCR, Copy_u8Line + 1);
      break;
    }
  }
  if (Copy_u8Line == EXTI_LINE2)
  {
    switch (Copy_u8SenseMode)
    {
    case EXTI_FALLING_EDGE:
      CLR_BIT(MCUCSR, 6);
      break;
    case EXTI_RISING_EDGE:
      SET_BIT(MCUCSR, 6);
      break;
      ;
    }
  }
}

/*___________________________________________________________________________________________________________________*/

/*---------------------------------------------------------------------------------------------------------------------------------
 *         	                 This Function used to disable the EINT Line
 *                           *-----------------------------------------------*
 * Parameters :
 *		Copy_u8Line  => [EXTI_LINEx](x=0..2)
 *
 * return     : Error status with type u8
 */
u8 EXTI_vDisableInterrupt(u8 Copy_u8Line)
{
  u8 Local_u8ErrorState = OK;
  if ((Copy_u8Line == EXTI_LINE0) || (Copy_u8Line == EXTI_LINE1) || (Copy_u8Line == EXTI_LINE2))
  {
    /* Clear The Required BIT */
    CLR_BIT(GICR, Copy_u8Line);
  }
  else
  {
    Local_u8ErrorState = NOK;
  }
  return Local_u8ErrorState;
}

/*___________________________________________________________________________________________________________________*/

/*---------------------------------------------------------------------------------------------------------------------------------
 *         	                 This Function used to enable the EINT Line
 *                           *-----------------------------------------------*
 * Parameters :
 *		Copy_u8Line  => [EXTI_LINEx](x=0..2)
 *
 * return     : Error status with type u8
 */
u8 EXTI_vEnableInterrupt(u8 Copy_u8Line)
{
  u8 Local_u8ErrorState = OK;
  if ((Copy_u8Line == EXTI_LINE0) || (Copy_u8Line == EXTI_LINE1) || (Copy_u8Line == EXTI_LINE2))
  {
    SET_BIT(GICR, Copy_u8Line);
  }
  else
  {
    Local_u8ErrorState = NOK;
  }
  return Local_u8ErrorState;
}

/*___________________________________________________________________________________________________________________*/

/*---------------------------------------------------------------------------------------------------------------------------------------
 *         	                       This Function used to clear the EINT flag
 *                                 *----------------------------------------------*
 * Parameters :
 *		Copy_u8Line  => [EXTI_LINEx](x=0..2)
 *
 * return     : nothing
 */
void EXTI_vClearFlag(u8 Copy_u8Line)
{
  SET_BIT(GIFR, Copy_u8Line);
}

/*___________________________________________________________________________________________________________________*/

/*-----------------------------------------------------------------------------------------------------------------------------------------
 *         	                         This Function used to Read the value of the EINT flag
 *                                   *------------------------------------------------------*
 * Parameters :
 *		Copy_u8Line  => [EXTI_LINEx](x=0..2)
 *
 * return     : Reading value
 */
u8 EXTI_u8GETFlag(u8 Copy_u8Line)
{

  return READ_BIT(GIFR, Copy_u8Line);
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------
 *         	                                  This Function Init THE EXTI
 *                                            *--------------------------------*
 * Parameters :
 *		Copy_pvoidCallBack => The Adress of ISR Func (its name)
 * 		Copy_u8Line        => [EXTI_LINE0 , EXTI_LINE1 , EXTI_LINE2]
 *
 * return     : Error status with type u8
 */
u8 EXTI_vSetCallBack(void (*Copy_pvCallBack)(void), u8 Copy_u8Line)
{
  u8 Local_u8ErrorState = OK;
  if (Copy_pvCallBack != NULL)
  {
    if (Copy_u8Line == EXTI_LINE0)
    {

      EXTI_CallBack[0] = Copy_pvCallBack;
    }
    else if (Copy_u8Line == EXTI_LINE1)
    {

      EXTI_CallBack[1] = Copy_pvCallBack;
    }
    else if (Copy_u8Line == EXTI_LINE2)
    {

      EXTI_CallBack[2] = Copy_pvCallBack;
    }
    else
    {
      Local_u8ErrorState = NOK;
    }
  }
  else
  {
    Local_u8ErrorState = NOK;
  }

  return Local_u8ErrorState;
}
/*___________________________________________________________________________________________________________________*/

/* ISR --> Implementation */

void __vector_1(void)              __attribute__((signal));
void __vector_1(void)
{

  if (EXTI_CallBack[0] != NULL)
  {

    EXTI_CallBack[0]();
    EXTI_vClearFlag(EXTI_LINE0);
  }
}

void __vector_2(void)            __attribute__((signal));
void __vector_2(void)
{

  if (EXTI_CallBack[1] != NULL)
  {

    EXTI_CallBack[1]();
    EXTI_vClearFlag(EXTI_LINE1);
  }
}

void __vector_3(void)              __attribute__((signal));
void __vector_3(void) 
{

  if (EXTI_CallBack[2] != NULL)
  {

    EXTI_CallBack[2]();
    EXTI_vClearFlag(EXTI_LINE2);
  }
}
