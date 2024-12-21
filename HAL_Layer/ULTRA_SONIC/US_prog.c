/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    US_prog.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : Ultra Sonic
 *
 */

#include "STD_MACROS.h"
#include "STD_TYPES.h"

#include <util/delay.h>

#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"
#include "TIMER_config.h"

#include "US_interface.h"
#include "US_private.h"
#include "US_config.h"

void US_vInit()
{
  DIO_enumSetPinDir(US_TRIG_PORT, US_TRIG_PIN, DIO_PIN_OUTPUT);
}

u8 US_u8ReadDistance(void)
{
  u16 a, b, high;
  u8 dis;
  TCCR1A = 0;
  TIFR = (1 << TIFR_ICF1); /* Clear ICF (Input Capture flag)  */

  /* Send rising edge for US_Trig */
  DIO_enumWritePinVal(US_TRIG_PORT, US_TRIG_PIN, DIO_HIGH);
  _delay_us(50);
  DIO_enumWritePinVal(US_TRIG_PORT, US_TRIG_PIN, DIO_LOW);

  TCCR1B = 0xc1; /* Rising edge, no prescaler , noise canceler*/
  while (READ_BIT(TIFR, TIFR_ICF1) == 0);
  a = ICR1;                  /* Take value of capture register */
  SET_BIT(TIFR, TIFR_ICF1);  /* Clear ICF flag */

  TCCR1B = 0x81; /* Falling edge, no prescaler ,noise canceler*/
  while (READ_BIT(TIFR, TIFR_ICF1) == 0);
  b = ICR1;                /* Take value of capture register */
  SET_BIT(TIFR, TIFR_ICF1); /* Clear ICF flag */
  TCNT1 = 0;
  TCCR1B = 0; /* Stop the timer */

  high = b - a;
  dis = ((high * 34600 * TIMER1_PRESCALER) / (F_CPU * 2));
  return dis;
}