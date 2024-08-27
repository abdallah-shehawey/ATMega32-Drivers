/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LED_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : LED
 *
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/*PORT Defines*/
#define PORTA                        0
#define PORTB                        1
#define PORTC                        2
#define PORTD                        3

/*PIN Defines*/
#define PIN0                         0
#define PIN1                         1
#define PIN2                         2
#define PIN3                         3
#define PIN4                         4
#define PIN5                         5
#define PIN6                         6
#define PIN7                         7
#define PIN8                         8

#define HIGH                         1
#define LOW                          0

#define ACTIVE_HIGH                  1
#define ACTIVE_LOW                   0

typedef struct
{
  u8 PortName       ;
  u8 PinNumber      ;
  u8 ActiveState    ;
} LED_config;

/*
LED_config LED0 = {DIO_PORTA, DIO_PIN0, HIGH};
*/

void LED_vInit                       (LED_config LED_Configutation);
void LED_vTurnOn                     (LED_config LED_Configutation);
void LED_vTurnOff                    (LED_config LED_Configutation);
void LED_vTog                        (LED_config LED_Configutation);

#endif /* LED_INTERFACE_H_ */
