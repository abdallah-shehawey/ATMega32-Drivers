/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    Servo_Motro_prog.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : Servo Motor
 *
 */
#include "STD_MACROS.h"
#include "STD_TYPES.h"

#include "Servo_Motor_interface.h"
#include "Servo_Motor_config.h"
#include "Servo_Motor_private.h"
#include "DIO_interface.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"

void SM_vInit(void)
{
  DIO_enumSetPinDir(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);
}

void SM_vTimer1Degree(s8 degree)
{
  TCNT1 = 0;
  double value = degree * .005555555556;

  if (0 < value <= 90)
  {
    value += 1.5;
  }
  else if (-90 <= value < 0)
  {
    value -= 1.5;
  }
  OCR1A = value * 1000;
}
