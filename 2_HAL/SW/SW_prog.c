/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SW_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : SWITCH / BUTTON
 *
 */
#include "STD_MACROS.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "SW_interface.h"
#include "SW_config.h"
#include "SW_private.h"

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function initialize the pin which connected to Push Button as Pull Up Input pin
 * Parameters :   => struct has the switch port , pin , status
 * return : void
 */
void SW_vInit(SW_Config SW_Configuration)
{
  DIO_enumSetPinDir(SW_Configuration.PortName, SW_Configuration.PinNumber, DIO_PIN_INPUT);

  /* If Sw is Internal Pull Up */
  if (SW_Configuration.PullState == SW_INT_PULL_UP)
  {
    DIO_enumWritePinVal(SW_Configuration.PortName, SW_Configuration.PinNumber, DIO_PIN_HIGH);

    /* we could use DIO_enumConnectPullup */
  }
}

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function read Button status
 * Parameters :   => struct has the switch port , pin , status
 * return : switch status
 */
u8 SW_u8Read(SW_Config SW_Configuration)
{
  u8 LOC_u8PinVal = SW_NOT_PRESSED;
  u8 LOC_u8Result = SW_NOT_PRESSED;

  if ((SW_Configuration.PullState == SW_INT_PULL_UP) || (SW_Configuration.PullState == SW_EXT_PULL_UP))
  {
    DIO_enumReadPinVal(SW_Configuration.PortName, SW_Configuration.PinNumber, &LOC_u8PinVal);

    if (LOC_u8PinVal == 0)
    {
      LOC_u8Result = SW_PREESED;
    }
    else if (LOC_u8PinVal == 1)
    {
      LOC_u8Result = SW_NOT_PRESSED;
    }
  }
  else if (SW_Configuration.PullState == SW_EXT_PULL_DOWN)
  {
    DIO_enumReadPinVal(SW_Configuration.PortName, SW_Configuration.PinNumber, &LOC_u8PinVal);

    if (LOC_u8PinVal == 1)
    {
      LOC_u8Result = SW_PREESED;
    }
    else if (LOC_u8PinVal == 0)
    {
      LOC_u8Result = SW_NOT_PRESSED;
    }
  }

  return LOC_u8Result;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    END    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>