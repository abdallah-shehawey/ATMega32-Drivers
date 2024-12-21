/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    BUZ_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : BUZZER
 *
 */

#ifndef BUZ_INTERFACE_H_
#define BUZ_INTERFACE_H_

/*PORT Defines*/
#define PORTA                         0
#define PORTB                         1
#define PORTC                         2
#define PORTD                         3

/*PIN Defines*/
#define PIN0                          0
#define PIN1                          1
#define PIN2                          2
#define PIN3                          3
#define PIN4                          4
#define PIN5                          5
#define PIN6                          6
#define PIN7                          7
#define PIN8                          8

#define HIGH                          1
#define LOW                           0

#define ACTIVE_HIGH                   1
#define ACTIVE_LOW                    0

typedef struct
{
  u8 PortName;
  u8 PinNumber;
  u8 ActiveState;
} BUZ_config;

/*
BUZ_config LED0 = {DIO_PORTA, DIO_PIN0, HIGH};
*/

void BUZ_vInit       (BUZ_config LED_Configutation);
void BUZ_vOn         (BUZ_config LED_Configutation);
void BUZ_vOff        (BUZ_config LED_Configutation);
void BUZ_vTog        (BUZ_config LED_Configutation);

#endif /* BUZ_INTERFACE_H_ */
