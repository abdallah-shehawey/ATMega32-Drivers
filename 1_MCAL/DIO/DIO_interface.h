/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DIO_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : GPIO/DIO
 *
 */

#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_

#include "STD_TYPES.h"

typedef enum // it should be before functions prototypes
{
  DIO_NOK,
  DIO_OK,
} DIO_errorStatus;

/*Port Defines*/
#define DIO_PORTA           0
#define DIO_PORTB           1
#define DIO_PORTC           2
#define DIO_PORTD           3

#define DIO_PIN0            0
#define DIO_PIN1            1
#define DIO_PIN2            2
#define DIO_PIN3            3
#define DIO_PIN4            4
#define DIO_PIN5            5
#define DIO_PIN6            6
#define DIO_PIN7            7

/*PIN Directions*/
#define DIO_PIN_OUTPUT      1
#define DIO_PIN_INPUT       0

/*PIN Value Options*/
#define DIO_PIN_HIGH        1
#define DIO_PIN_LOW         0
#define HIGH                1
#define LOW                 0
#define DIO_HIGH            1
#define DIO_LOW             0
#define DIO_INPUT           0
#define DIO_OUTPUT          1

/*PORT Directions*/
#define DIO_PORT_OUTPUT     0xFF
#define DIO_PORT_INPUT      0

/*PORT Value Options*/
#define DIO_PORT_HIGH       0xFF
#define DIO_PORT_LOW        0

// Pull UP
#define PUD                 2

/*IO Pins*/
DIO_errorStatus DIO_enumSetPinDir          (u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Direction);
DIO_errorStatus DIO_enumWritePinVal        (u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Value);
DIO_errorStatus DIO_enumReadPinVal         (u8 Copy_u8PORT, u8 Copy_u8PIN, u8 *Copy_Pu8Data);
DIO_errorStatus DIO_enumTogglePinVal       (u8 Copy_u8PORT, u8 Copy_u8PIN);

/*Internal Pull UP*/
DIO_errorStatus DIO_enumConnectPullUp      (u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8ConnectPullup);

/*IO Ports*/
DIO_errorStatus DIO_enumSetPortDir         (u8 Copy_u8PORT, u8 Copy_u8Direction);
DIO_errorStatus DIO_enumWritePortVal       (u8 Copy_u8PORT, u8 portValue);
DIO_errorStatus DIO_enumReadPorVal         (u8 Copy_u8PORT,u8 *Copy_PtrData);
DIO_errorStatus DIO_enumTogglePortValue    (u8 Copy_u8PORT);

/*IO Nibbles*/
DIO_errorStatus DIO_vSetLowNibbleDir       (u8 Copy_u8PORT, u8 value);
DIO_errorStatus DIO_vSetHighNibbleDir      (u8 Copy_u8PORT, u8 value);
DIO_errorStatus DIO_vWriteLowNibble        (u8 Copy_u8PORT, u8 value);
DIO_errorStatus DIO_vWriteHighNibble       (u8 Copy_u8PORT, u8 value);


#endif
