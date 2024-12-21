/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    CLCD_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : CLCD
 *
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/*___________________________________________________________________________________________________________________*/

/* LCD Mode */
/*
*Choose 8 for 8_BIT Connection, 4 for 4_BIT Connection
*Option
  1- 4
  2- 8
*/
#define CLCD_MODE 8

#if CLCD_MODE == 4
/*
*Optoins :-
  1- CLCD_HIGH_NIBBLE
  2- CLCD_LOW_NIBBLE
*/
#define CLCD_DATA_NIBBLE CLCD_LOW_NIBBLE

#endif

/*___________________________________________________________________________________________________________________*/

/*
*Optoins :-
  1- CLCD_DISPLAYON_CURSOROFF
  2- CLCD_DISPLAYOFF_CURSOROFF
  3- CLCD_DISPLAYON_CURSORON
  4- CLCD_DISPLAYON_CURSORON_BLINK
*/

#define CLCD_DISPLAY_CURSOR CLCD_DISPLAYON_CURSORON

/*___________________________________________________________________________________________________________________*/

/*
*Optoins :-
  1-DIO_PORTA
  2-DIO_PORTB
  3-DIO_PORTC
  4-DIO_PORTD
*/

/* D0:D7 */
#define CLCD_DATA_PORT DIO_PORTA
/* RS, RW, EN */
#define CLCD_CONTROL_PORT DIO_PORTB

/*___________________________________________________________________________________________________________________*/

/*
*Optoins :-
  1-DIO_PIN0
  2-DIO_PIN1
  3-DIO_PIN2
  4-DIO_PIN3
  5-DIO_PIN4
  6-DIO_PIN5
  7-DIO_PIN6
  8-DIO_PIN7
*/

#define CLCD_RS DIO_PIN0
#define CLCD_RW DIO_PIN1
#define CLCD_EN DIO_PIN2

#endif /* CLCD_CONFIG_H_ */
