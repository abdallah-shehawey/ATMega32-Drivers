/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DIO_program.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : GPIO/DIO
 *
 */

#include "STD_MACROS.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "DIO_private.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                          IO Pins                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function set the direction of the Pin  (INPUT || OUTPUT)
 * Parameters :
      =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
      =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
      =>Copy_u8Direction --> Pin Direction [ DIO_PIN_OUTPUT , DIO_PIN_INPUT ]
 * return : its status
 */

DIO_errorStatus DIO_enumSetPinDir(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Direction)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  /* Make sure that the Port ID and Pin ID are in the valid range */
  if ((Copy_u8PORT <= DIO_PORTD) && (Copy_u8PIN <= DIO_PIN7))
  {
    if (Copy_u8Direction == DIO_PIN_OUTPUT)
    {
      /* Check on the Required PORT Number */
      switch (Copy_u8PORT)
      {
      case DIO_PORTA:
        SET_BIT(DDRA_REG, Copy_u8PIN);
        break;
      case DIO_PORTB:
        SET_BIT(DDRB_REG, Copy_u8PIN);
        break;
      case DIO_PORTC:
        SET_BIT(DDRC_REG, Copy_u8PIN);
        break;
      case DIO_PORTD:
        SET_BIT(DDRD_REG, Copy_u8PIN);
        break;
      }
    }
    else if (Copy_u8Direction == DIO_PIN_INPUT)
    {
      /* Check on the Required PORT Number */
      switch (Copy_u8PORT)
      {
      case DIO_PORTA:
        CLR_BIT(DDRA_REG, Copy_u8PIN);
        break;
      case DIO_PORTB:
        CLR_BIT(DDRB_REG, Copy_u8PIN);
        break;
      case DIO_PORTC:
        CLR_BIT(DDRC_REG, Copy_u8PIN);
        break;
      case DIO_PORTD:
        CLR_BIT(DDRD_REG, Copy_u8PIN);
        break;
      }
    }
    else
    {
      LOC_enumState = DIO_NOK;
    }
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }
  return LOC_enumState;
}
/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function set the Value of the Pin  (HIGH || LOW)
 * Parameters :
      =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
      =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
      =>Copy_u8Value --> Pin Direction [ DIO_PIN_HIGH , DIO_PIN_LOW ]
 * return : its status
 */
DIO_errorStatus DIO_enumWritePinVal(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Value)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  /* Make sure that the Port ID and Pin ID are in the valid range */
  if ((Copy_u8PORT <= DIO_PORTD) && (Copy_u8PIN <= DIO_PIN7))
  {
    if (Copy_u8Value == DIO_PIN_OUTPUT)
    {
      /* Check on the Required PORT Number */
      switch (Copy_u8PORT)
      {
      case DIO_PORTA:
        SET_BIT(PORTA_REG, Copy_u8PIN);
        break;
      case DIO_PORTB:
        SET_BIT(PORTB_REG, Copy_u8PIN);
        break;
      case DIO_PORTC:
        SET_BIT(PORTC_REG, Copy_u8PIN);
        break;
      case DIO_PORTD:
        SET_BIT(PORTD_REG, Copy_u8PIN);
        break;
      }
    }
    else if (Copy_u8Value == DIO_PIN_INPUT)
    {
      /* Check on the Required PORT Number */
      switch (Copy_u8PORT)
      {
      case DIO_PORTA:
        CLR_BIT(PORTA_REG, Copy_u8PIN);
        break;
      case DIO_PORTB:
        CLR_BIT(PORTB_REG, Copy_u8PIN);
        break;
      case DIO_PORTC:
        CLR_BIT(PORTC_REG, Copy_u8PIN);
        break;
      case DIO_PORTD:
        CLR_BIT(PORTD_REG, Copy_u8PIN);
        break;
      }
    }
    else
    {
      LOC_enumState = DIO_NOK;
    }
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }
  return LOC_enumState;
}
/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function Get the Value of the Pin
 * Parameters :
      =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
      =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
      => *Copy_PtrData  --> pointer to recieve the pin value
 * return : its status and recieve Pin Value in pointer
 */
DIO_errorStatus DIO_enumReadPinVal(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 *Copy_Pu8Data)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD) && (Copy_u8PIN <= DIO_PIN7))
  {
    /* Check on the Required PORT Number */
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      *Copy_Pu8Data = READ_BIT(PINA_REG, Copy_u8PIN);
      break;
    case DIO_PORTB:
      *Copy_Pu8Data = READ_BIT(PINB_REG, Copy_u8PIN);
      break;
    case DIO_PORTC:
      *Copy_Pu8Data = READ_BIT(PINC_REG, Copy_u8PIN);
      break;
    case DIO_PORTD:
      *Copy_Pu8Data = READ_BIT(PIND_REG, Copy_u8PIN);
      break;
    }
  }
  else
  {
    /* in case of error in the Pin ID or PORT ID */
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}
/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function Toggle the Value of the Pin
 * Parameters :
      =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
      =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
 * return : its status
 */
DIO_errorStatus DIO_enumTogglePinVal(u8 Copy_u8PORT, u8 Copy_u8PIN)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD) && (Copy_u8PIN <= DIO_PIN7))
  {
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      TOG_BIT(PORTA_REG, Copy_u8PIN);
      break;
    case DIO_PORTB:
      TOG_BIT(PORTB_REG, Copy_u8PIN);
      break;
    case DIO_PORTC:
      TOG_BIT(PORTC_REG, Copy_u8PIN);
      break;
    case DIO_PORTD:
      TOG_BIT(PORTD_REG, Copy_u8PIN);
      break;
    }
  }
  else
  {
    /* in case of error in the Pin ID or PORT ID */
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}
/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function connected internal pull up
 * Parameters :
      =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
      =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
    =>Copy_u8ConnectPullup --> [DIO_PIN_HIGH , DIO_PIN_LOW ]
 * return : its status
 */
DIO_errorStatus DIO_enumConnectPullUp(u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8ConnectPullup)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD) && (Copy_u8PIN <= DIO_PIN7))
  {
    switch (Copy_u8PORT)
    {
    /* Connect or disconnect the pull up resistance to the given pin in port A */
    case DIO_PORTA:
      if (Copy_u8ConnectPullup == DIO_PIN_HIGH)
      {
        CLR_BIT(SFIOR_REG, PUD); // It's default is zero
        CLR_BIT(DDRA_REG, Copy_u8PIN);
        SET_BIT(PORTA_REG, Copy_u8PIN);
      }
      else
      {
        CLR_BIT(PORTA_REG, Copy_u8PIN);
      }
      break;
      /* Connect or disconnect the pull up resistance to the given pin in port B */
    case DIO_PORTB:
      if (Copy_u8ConnectPullup == DIO_PIN_HIGH)
      {
        CLR_BIT(SFIOR_REG, PUD);
        CLR_BIT(DDRB_REG, Copy_u8PIN);
        SET_BIT(PORTB_REG, Copy_u8PIN);
      }
      else
      {
        CLR_BIT(PORTB_REG, Copy_u8PIN);
      }
      break;
      /* Connect or disconnect the pull up resistance to the given pin in port C */
    case DIO_PORTC:
      if (Copy_u8ConnectPullup == DIO_PIN_HIGH)
      {
        CLR_BIT(SFIOR_REG, PUD);
        CLR_BIT(DDRC_REG, Copy_u8PIN);
        SET_BIT(PORTC_REG, Copy_u8PIN);
      }
      else
      {
        CLR_BIT(PORTC_REG, Copy_u8PIN);
      }
      break;
      /* Connect or disconnect the pull up resistance to the given pin in port D */
    case DIO_PORTD:
      if (Copy_u8ConnectPullup == DIO_PIN_HIGH)
      {
        CLR_BIT(SFIOR_REG, PUD);
        CLR_BIT(DDRD_REG, Copy_u8PIN);
        SET_BIT(PORTD_REG, Copy_u8PIN);
      }
      else
      {
        CLR_BIT(PORTD_REG, Copy_u8PIN);
      }
      break;
    }
  }

  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}
/*___________________________________________________________________________________________________________________*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                          IO PORTS                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//---------------------------------------------------------------------------------------------------------------------------------------------------

/*
 * Breif : This Function Set the direction of the port (INPUT / OUTPUT)
 * Parameters :
    =>Copy_u8PORT --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
    =>Copy_u8Direction  --> Port direction [ DIO_PORT_OUTPUT , DIO_PORT_INPUT ]
 * return :  its status
 */
DIO_errorStatus DIO_enumSetPortDir(u8 Copy_u8PORT, u8 Copy_u8Direction)
{
  DIO_errorStatus LOC_enumState = DIO_OK;
  if ((Copy_u8PORT <= DIO_PORTD))
  {
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      DDRA_REG = Copy_u8Direction;
      break;
    case DIO_PORTB:
      DDRB_REG = Copy_u8Direction;
      break;
    case DIO_PORTC:
      DDRC_REG = Copy_u8Direction;
      break;
    case DIO_PORTD:
      DDRD_REG = Copy_u8Direction;
      break;
    default:
      LOC_enumState = DIO_NOK;
      break;
    }
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }
  return LOC_enumState;
}
/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function Set value on Port
 * Parameters :
      =>Copy_u8PORT --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
    =>Copy_u8Value  --> The Value  [DIO_PORT_HIGH , DIO_PORT_LOW , Another Value]
 * return : its status
 */
DIO_errorStatus DIO_enumWritePortVal(u8 Copy_u8PORT, u8 Copy_u8Value)
{
  DIO_errorStatus LOC_enumState = DIO_OK;
  if ((Copy_u8PORT <= DIO_PORTD) && ((Copy_u8Value <= 255) || (Copy_u8Value == DIO_PORT_LOW) || (Copy_u8Value == DIO_PORT_HIGH)))
  {
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      PORTA_REG= Copy_u8Value;
      break;
    case DIO_PORTB:
      PORTB_REG = Copy_u8Value;
      break;
    case DIO_PORTC:
      PORTC_REG = Copy_u8Value;
      break;
    case DIO_PORTD:
      PORTD_REG = Copy_u8Value;
      break;
    default:
      LOC_enumState = DIO_NOK;
      break;
    }
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }
  return LOC_enumState;
}
/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function GET value on Port
 * Parameters :
    =>Copy_u8PORT --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
    => *Copy_PtrData  --> pointer to recieve the port value
 * return : its status and recieve Port Value in pointer
 */
DIO_errorStatus DIO_enumReadPorVal(u8 Copy_u8PORT, u8 *Copy_Pu8Data)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD))
  {
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      *Copy_Pu8Data = PINA_REG;
      break;
    case DIO_PORTB:
      *Copy_Pu8Data = PINB_REG;
      break;
    case DIO_PORTC:
      *Copy_Pu8Data = PINC_REG;
      break;
    case DIO_PORTD:
      *Copy_Pu8Data = PIND_REG;
      break;
    default:
      LOC_enumState = DIO_NOK;
      break;
    }
    return LOC_enumState;
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }
  return LOC_enumState;
}
/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function Toggle value on Port
 * Parameters :
    =>Copy_u8PORT --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 * return : its status
 */
DIO_errorStatus DIO_enumTogglePortValue(u8 Copy_u8PORT)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  if (Copy_u8PORT <= DIO_PORTD)
  {
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      PORTA_REG = ~PORTA_REG;
      break;
    case DIO_PORTB:
      PORTB_REG = ~PORTB_REG;
      break;
    case DIO_PORTC:
      PORTC_REG = ~PORTC_REG;
      break;
    case DIO_PORTD:
      PORTD_REG = ~PORTD_REG;
      break;
    }
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }
  return LOC_enumState;
}
/*___________________________________________________________________________________________________________________*/

//---------------------------------------------------------------------------------------------------------------------------------------------------
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                          IO NIBBLES                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function write value on low nibbles of the Port
 * Parameters :
    =>Copy_u8PORT  --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
    =>Copy_u8value --> to set its low bits on high nibble oh register
 * return : its status
 *
 *Hint1 : Low Nibbles = Least Pins [0:3]
 *Hint2 : This Function also take the first 4 bits from the value (#) => xxxx#### AND put it in low nobbles
 *
 */
DIO_errorStatus DIO_vWriteLowNibble(u8 Copy_u8PORT, u8 value)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD))
  {
    value &= 0x0F;
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      PORTA_REG &= 0xF0; // Set only the high nibble of the port A by the given value
      PORTA_REG |= value;
      break;
    case DIO_PORTB:
      PORTB_REG &= 0xF0; // Set only the high nibble of the port B by the given value
      PORTB_REG |= value;
      break;
    case DIO_PORTC:
      PORTC_REG &= 0xF0; // Set only the high nibble of the port C by the given value
      PORTC_REG |= value;
      break;
    case DIO_PORTD:
      PORTD_REG &= 0xF0; // Set only the high nibble of the port D by the given value
      PORTD_REG |= value;
      break;
    default:
      break;
    }
  }

  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}
/*
DIO_ErrorStatus DIO_vWriteLowNibble(u8 Copy_u8PORT, u8 value)
{
  DIO_vWritePinVal(Copy_u8PORT, DIO_PIN0, READ_BIT(value, DIO_PIN0));
  DIO_vWritePinVal(Copy_u8PORT, DIO_PIN1, READ_BIT(value, DIO_PIN1));
  DIO_vWritePinVal(Copy_u8PORT, DIO_PIN2, READ_BIT(value, DIO_PIN2));
  DIO_vWritePinVal(Copy_u8PORT, DIO_PIN3, READ_BIT(value, DIO_PIN3));
}
*/
/*___________________________________________________________________________________________________________________*/
/*
 * Breif : This Function write value on high nibbles of the Port
 * Parameters :
    =>Copy_u8PORT  --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
    =>Copy_u8value --> to set its high bits on high nibble oh register
 * return : its status
 *
 *Hint1 : High Nibbles = Most Pins [4:7]
 *Hint2 : This Function take the first 4 bits from the value (#) => xxxx#### AND put it in high nobbles
 *
 */
DIO_errorStatus DIO_vWriteHighNibble(u8 Copy_u8PORT, u8 value)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD))
  {
    value <<= 4;
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      PORTA_REG &= 0x0F;
      PORTA_REG|= value;
      break;
    case DIO_PORTB:
      PORTB_REG &= 0x0F;
      PORTB_REG |= value;
      break;
    case DIO_PORTC:
      PORTC_REG &= 0x0F;
      PORTC_REG |= value;
      break;
    case DIO_PORTD:
      PORTD_REG &= 0x0F;
      PORTD_REG |= value;
      break;
    default:
      break;
    }
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}

/*___________________________________________________________________________________________________________________*/

DIO_errorStatus DIO_vSetLowNibbleDir(u8 Copy_u8PORT, u8 value)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD))
  {
    value &= 0x0F;
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      DDRA_REG &= 0xF0; // Set only the high nibble of the port A by the given value
      DDRA_REG |= value;
      break;
    case DIO_PORTB:
      DDRB_REG &= 0xF0; // Set only the high nibble of the port B by the given value
      DDRB_REG |= value;
      break;
    case DIO_PORTC:
      DDRC_REG &= 0xF0; // Set only the high nibble of the port C by the given value
      DDRC_REG |= value;
      break;
    case DIO_PORTD:
      DDRD_REG &= 0xF0; // Set only the high nibble of the port D by the given value
      DDRD_REG|= value;
      break;
    default:
      break;
    }
  }

  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}

/*___________________________________________________________________________________________________________________*/

DIO_errorStatus DIO_vSetHighNibbleDir(u8 Copy_u8PORT, u8 value)
{
  DIO_errorStatus LOC_enumState = DIO_OK;

  if ((Copy_u8PORT <= DIO_PORTD))
  {
    value <<= 4;
    switch (Copy_u8PORT)
    {
    case DIO_PORTA:
      DDRA_REG &= 0x0F;
      DDRA_REG |= value;
      break;
    case DIO_PORTB:
      DDRB_REG &= 0x0F;
      DDRB_REG |= value;
      break;
    case DIO_PORTC:
      DDRC_REG &= 0x0F;
      DDRC_REG |= value;
      break;
    case DIO_PORTD:
      DDRD_REG &= 0x0F;
      DDRD_REG |= value;
      break;
    default:
      break;
    }
  }
  else
  {
    LOC_enumState = DIO_NOK;
  }

  return LOC_enumState;
}

//________________________________________________________________    END    ____________________________________________________________________________
