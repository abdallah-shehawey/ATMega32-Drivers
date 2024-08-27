/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    USART_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : USART
 *
 */

#include "STD_TYPES.h"
#include "STD_MACROS.h"

#include <util/delay.h>

#include "DIO_interface.h"

#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"

/*Global variable to carry the send Data*/
static const u8 *USART_pu8SendData = NULL;

/*Global variable to carry the Receive Data*/
static u8 *USART_pu8ReceiveData = NULL;

/*Global variable to carry the buffer size*/
static u8 USART_u8BufferSize;

/*Global variable to indicate for the current Data index of the buffer*/
static u8 USART_u8Index;

/*Global pointer to function to carry the notification function called by ISR*/
static void (*USART_pvNotificationFunc)(void) = NULL;

/*Global flag for the USART Busy State*/
static u8 USART_u8State = IDLE;

/*___________________________________________________________________________________________________________________*/

/*
 * Breif      : This Function initialize USART depend on config.h
 * Parameters :  Nothing
 * return     :  Nothing
 */
void USART_vInit(void)
{
  /* We will adjust this value according to the configrations then store it in UCSRC in one operation */
  u8 Local_u8UCSRC = 0;

  /***** Check 3 Modes   *****/
#if (USART_MODE == ASYNCHRONOUS) && (USART_SYSTEM_SPEED == USART_1X)

  CLR_BIT(UCSRA, UCSRA_U2X);

  /*Calculate The Baud Rate From The Equation */
  u16 Local_u16UBRR = (u16)((SYSTEM_FREQUENCY / (16 * USART_BAUD_RATE)) - 1);

#elif (USART_MODE == ASYNCHRONOUS) && (USART_SYSTEM_SPEED == USART_2X)

  SET_BIT(UCSRA, UCSRA_U2X);

  /*Calculate The Baud Rate From The Equation */
  u16 Local_u16UBRR = (u16)((SYSTEM_FREQUENCY / (8 * USART_BAUD_RATE)) - 1);

#elif (USART_MODE == SYNCHRONOUS)

  /*Calculate The Baud Rate From The Equation */
  u16 Local_u16UBRR = (u16)((SYSTEM_FREQUENCY / (2 * USART_BAUD_RATE)) - 1);

#else

#error "Wrong USART_MODE or USART_SYSTEM_SPEED config"

#endif
  /*
      $ Set Baud Rate
      Hint : UBRRH then UBRRL to avoid problems
   */
  UBRRH = (u8)(Local_u16UBRR << 8); /* MSBs at Local_u16UBRR */
  UBRRL = (u8)Local_u16UBRR;
  /*___________________________________________________________________________________________________________________*/

  /*Multi-Processor Communication mode*/
#if USART_MPCM == DISABLE
  CLR_BIT(UCSRA, UCSRA_MPCM);
#elif USART_MPCM == ENABLE
  SET_BIT(UCSRA, UCSRA_MPCM);
#else
#error "Wrong USART_MPCM config"
#endif

  /*___________________________________________________________________________________________________________________*/

  /*UCSRC Register Config*/

  /*USART Mode*/
#if USART_MODE == ASYNCHRONOUS
  CLR_BIT(Local_u8UCSRC, UCSRC_UMSEL);
#elif USART_MODE == SYNCHRONOUS
  SET_BIT(Local_u8UCSRC, UCSRC_UMSEL);
#else
#error "Wrong USART_MODE config"
#endif

  /*Parity Mode*/
#if USART_PARITY_MODE == DISABLE

  CLR_BIT(Local_u8UCSRC, UCSRC_UPM0);
  CLR_BIT(Local_u8UCSRC, UCSRC_UPM1);

#elif USART_PARITY_MODE == EVEN_PARITY

  CLR_BIT(Local_u8UCSRC, UCSRC_UPM0);
  SET_BIT(Local_u8UCSRC, UCSRC_UPM1);

#elif USART_PARITY_MODE == ODD_PARIT

  SET_BIT(Local_u8UCSRC, UCSRC_UPM0);
  SET_BIT(Local_u8UCSRC, UCSRC_UPM1);

#else

#error "Wrong USART_PARITY_MODE config"

#endif

  /*Stop Bit*/
#if USART_STOP_BIT == STOP_BIT_1

  CLR_BIT(Local_u8UCSRC, UCSRC_USBS);

#elif USART_STOP_BIT == STOP_BIT_2

  SET_BIT(Local_u8UCSRC, UCSRC_USBS);

#else

#error "Wrong USART_STOP_BIT config"

#endif

  /*Data Size*/
#if USART_DATA_SIZE == DATA_SIZE_5_BIT

  CLR_BIT(Local_u8UCSRC, UCSRC_UCSZ0);
  CLR_BIT(Local_u8UCSRC, UCSRC_UCSZ1);
  CLR_BIT(UCSRB, UCSRB_UCSZ2);

#elif USART_DATA_SIZE == DATA_SIZE_6_BIT

  SET_BIT(Local_u8UCSRC, UCSRC_UCSZ0);
  CLR_BIT(Local_u8UCSRC, UCSRC_UCSZ1);
  CLR_BIT(UCSRB, UCSRB_UCSZ2);

#elif USART_DATA_SIZE == DATA_SIZE_7_BIT

  CLR_BIT(Local_u8UCSRC, UCSRC_UCSZ0);
  SET_BIT(Local_u8UCSRC, UCSRC_UCSZ1);
  CLR_BIT(UCSRB, UCSRB_UCSZ2);

#elif USART_DATA_SIZE == DATA_SIZE_8_BIT

  SET_BIT(Local_u8UCSRC, UCSRC_UCSZ0);
  SET_BIT(Local_u8UCSRC, UCSRC_UCSZ1);
  CLR_BIT(UCSRB, UCSRB_UCSZ2);

#elif USART_DATA_SIZE == DATA_SIZE_9_BIT

  SET_BIT(Local_u8UCSRC, UCSRC_UCSZ0);
  SET_BIT(Local_u8UCSRC, UCSRC_UCSZ1);
  SET_BIT(UCSRB, UCSRB_UCSZ2);

#else

#error "Wrong USART_DATA_SIZE config"

#endif

  /*Clock Polarity (for SYNCHRONOUS mode only)*/
#if USART_MODE == SYNCHRONOUS

#if USART_CLOCK_POLARITY == XCK_RISING_TX_XCH_FALLING_RX

  CLR_BIT(Local_u8UCSRC, UCSRC_UCPOL);

#elif USART_CLOCK_POLARITY == XCK_RISING_RX_XCH_FALLING_TX

  SET_BIT(Local_u8UCSRC, UCSRC_UCPOL);

#else

#error "Wrong USART_STOP_BIT config"

#endif

#endif

  /*Set UCSRC Mode*/
  SET_BIT(Local_u8UCSRC, UCSRC_URSEL);

  /*Store the value in UCSRC Register (one operation) */
  UCSRC = Local_u8UCSRC;

  /*___________________________________________________________________________________________________________________*/

  /* Finally Enable the components */

  /*RX Complete Interrupt Enable*/
#if USART_RX_COMPLETE_INTERRUPT == DISABLE
  CLR_BIT(UCSRB, UCSRB_RXCIE);
#elif USART_RX_COMPLETE_INTERRUPT == ENABLE
  SET_BIT(UCSRB, UCSRB_RXCIE);
#else
#error "Wrong USART_RX_COMPLETE_INTERRUPT config"
#endif

  /*TX Complete Interrupt Enable*/
#if USART_TX_COMPLETE_INTERRUPT == DISABLE
  CLR_BIT(UCSRB, UCSRB_TXCIE);
#elif USART_TX_COMPLETE_INTERRUPT == ENABLE
  SET_BIT(UCSRB, UCSRB_TXCIE);
#else
#error "Wrong USART_TX_COMPLETE_INTERRUPT config"
#endif

  /*UDR Empty Interrupt Enable*/
#if USART_UDR_EMPTY_INTERRUPT == DISABLE
  CLR_BIT(UCSRB, UCSRB_UDRIE);
#elif USART_UDR_EMPTY_INTERRUPT == ENABLE
  SET_BIT(UCSRB, UCSRB_UDRIE);
#else
#error "Wrong USART_UDR_EMPTY_INTERRUPT config"
#endif

  /*Receive Enable*/
#if USART_RECEIVER_ENABLE == DISABLE

  CLR_BIT(UCSRB, UCSRB_RXEN);

#elif USART_RECEIVER_ENABLE == ENABLE

  SET_BIT(UCSRB, UCSRB_RXEN);

#else

#error "Wrong USART_RECEIVER_ENABLE config"

#endif

  /*Transmitter Enable*/
#if USART_TRANSMITTER_ENABLE == DISABLE

  CLR_BIT(UCSRB, UCSRB_TXEN);

#elif USART_TRANSMITTER_ENABLE == ENABLE

  SET_BIT(UCSRB, UCSRB_TXEN);

#else

#error "Wrong USART_TRANSMITTER_ENABLE config"

#endif
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to Send Data from Tx to Rx
 *                                                *-----------------------------------------*
 * Parameters :
 *		Copy_u8Data => Data to be send
 *
 * return     : Error status with type u8
 */
u8 USART_u8SendData(u8 Copy_u8Data)
{
  u8 Local_u8ErrorState = OK;
  u32 Local_u32TimeoutCounter = 0;

  if (USART_u8State == IDLE)
  {
    USART_u8State = BUSY;

    /*
      Hint : TIMEOUT to avoid infinity loop
     */
    /*Wait until a Receiving complete or Timing out*/
    while (((READ_BIT(UCSRA, UCSRA_UDRE)) == 0) && (Local_u32TimeoutCounter != USART_u32TIMEOUT))
    {
      Local_u32TimeoutCounter++;
    }

    if (Local_u32TimeoutCounter == USART_u32TIMEOUT)
    {
      Local_u8ErrorState = TIMEOUT_STATE;
    }
    else
    {
      UDR = Copy_u8Data;
    }

    USART_u8State = IDLE;
  }
  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to receive Data from Tx to Rx
 *                                                *-----------------------------------------*
 * Parameters :
 *		Copy_u8ReceivedData => pointer to carry received data
 *
 * return     : Error status with type u8
 */
u8 USART_u8ReceiveData(u8 *Copy_u8ReceivedData)
{
  u8 Local_u8ErrorState = OK;
  u32 Local_u32TimeoutCounter = 0;

  if (Copy_u8ReceivedData != NULL)
  {
    if (USART_u8State == IDLE)
    {
      USART_u8State = BUSY;

      /*Wait until a receive complete*/
      while (((READ_BIT(UCSRA, UCSRA_RXC)) == 0) && (Local_u32TimeoutCounter != USART_u32TIMEOUT))
      {
        Local_u32TimeoutCounter++;
      }

      if (Local_u32TimeoutCounter == USART_u32TIMEOUT)
      {
        Local_u8ErrorState = TIMEOUT_STATE;
      }
      else
      {
        *Copy_u8ReceivedData = UDR;
      }

      USART_u8State = IDLE;
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
 *         	                                      A function to send string from Tx to Rx (polling)
 *                                                *--------------------------------------------------*
 * Parameters :
 *		Copy_pu8String => pointer that holds the data
 *
 * return     : Error status with type u8
 */
u8 USART_u8SendStringSynch(u8 *Copy_pu8String)
{
  u8 Local_u8ErrorState = OK;

  u32 Local_u32Index = 0;

  if (Copy_pu8String != NULL)
  {
    while (Copy_pu8String[Local_u32Index] != '\0')
    {
      Local_u8ErrorState = USART_u8SendData(Copy_pu8String[Local_u32Index]);
      _delay_ms(100);
      Local_u32Index++;
      if (Local_u8ErrorState != OK)
      {
        break;
      }
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
 *         	                                      A function to send string from Tx to Rx (Interrupt)
 *                                               *----------------------------------------------------*
 * Parameters :
 *		Copy_pu8String   => pointer that holds the data
 *      NotificationFunc => function that called after the transmit complete
 *
 * return     : Error status with type u8
 */
u8 USART_u8SendStringAsynch(u8 *Copy_pu8String, void (*NotificationFunc)(void))
{
  u8 Local_u8ErrorState = OK;

  if (USART_u8State == IDLE)
  {
    if ((Copy_pu8String != NULL) && (NotificationFunc != NULL))
    {
      /*USART is now Busy*/
      USART_u8State = BUSY;

      /*Assign the USART data globally*/
      USART_pu8SendData = Copy_pu8String;
      USART_pvNotificationFunc = NotificationFunc;

      /*Set Index to first element*/
      USART_u8Index = 0;

      /*Send first Data */
      UDR = USART_pu8SendData[USART_u8Index];

      /*USART Transmit Interrupt Enable*/
      SET_BIT(UCSRB, UCSRB_TXCIE);
    }
    else
    {
      Local_u8ErrorState = NULL_POINTER;
    }
  }
  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

/*___________________________________________________________________________________________________________________*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to receive buffer from Tx to Rx (polling)
 *                                             *----------------------------------------------------*
 * Parameters :
 *		Copy_pu8String     => pointer that holds the data
 *      Copy_u32BufferSize => size of array
 *
 * return     : Error status with type u8
 */
u8 USART_u8ReceiveBufferSynch(u8 *Copy_pu8String, u32 Copy_u32BufferSize)
{
  u8 Local_u8ErrorState = OK;

  if (Copy_pu8String != NULL)
  {
    for (u32 Local_u32Index = 0; Local_u32Index < Copy_u32BufferSize; Local_u32Index++)
    {
      Local_u8ErrorState = USART_u8ReceiveData(&Copy_pu8String[Local_u32Index]);
      if (Local_u8ErrorState != OK)
      {
        break;
      }
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
 *         	                                      A function to receive buffer from Tx to Rx (Interrupt)
 *                                             *----------------------------------------------------*
 * Parameters :
 *		Copy_pu8String     => pointer that holds the data
 *      Copy_u32BufferSize => size of array
 *      NotificationFunc   => function that called after the received complete
 *
 * return     : Error status with type u8
 */
u8 USART_u8ReceiveBufferAsynch(u8 *Copy_pu8String, u32 Copy_u32BufferSize, void (*NotificationFunc)(void))
{
  u8 Local_u8ErrorState = OK;

  if (USART_u8State == IDLE)
  {
    if ((Copy_pu8String != NULL) && (NotificationFunc != NULL))
    {
      /*USART is now Busy*/
      USART_u8State = BUSY;

      /*Assign the USART data globally*/
      USART_pu8ReceiveData = Copy_pu8String;
      USART_pvNotificationFunc = NotificationFunc;
      USART_u8BufferSize = Copy_u32BufferSize;

      /*Set Index to first element*/
      USART_u8Index = 0;

      /*USART Recieve Interrupt Enable */
      SET_BIT(UCSRB, UCSRB_RXCIE);
    }
    else
    {
      Local_u8ErrorState = NULL_POINTER;
    }
  }
  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

/*___________________________________________________________________________________________________________________*/

/* ISR for RX complete */
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
  /*Receive next Data*/
  USART_pu8ReceiveData[USART_u8Index] = UDR;

  /*Increment Data index of the buffer*/
  USART_u8Index++;

  if (USART_u8Index == USART_u8BufferSize)
  {
    /*Send Data Complete*/

    USART_u8Index = 0;
    /*USART is now IDLE*/
    USART_u8State = IDLE;

    /*Call Notification Function*/
    if (USART_pvNotificationFunc != NULL)
    {
      USART_pvNotificationFunc();
    }

    /*USART Recieve Interrupt Disable*/
    CLR_BIT(UCSRB, UCSRB_RXCIE);
  }
  else
  {
    /*Do Noting*/
  }
}

//-------------------------------------------------------------------------------------------------------------------------------
/* ISR for TX complete */
void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{

  /*Increment Data index of the buffer*/
  USART_u8Index++;

  if (USART_pu8SendData[USART_u8Index] == '\0')
  {
    /*Receive Data Complete*/
    USART_u8Index = 0;

    /*USART is now IDLE*/
    USART_u8State = IDLE;

    /*Call Notification Function*/
    if (USART_pvNotificationFunc != NULL)
    {
      USART_pvNotificationFunc();
    }

    /*USART Transmit Interrupt Disable*/
    CLR_BIT(UCSRB, UCSRB_TXCIE);
  }
  else
  {
    /*Send Data not Complete/
    /Send next Data*/
    UDR = USART_pu8SendData[USART_u8Index];
  }
}
