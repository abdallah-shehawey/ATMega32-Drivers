/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    US_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : Ultra Sonic
 *
 */

#ifndef US_CONFIG_H_
#define US_CONFIG_H_

#define F_CPU 1000000UL

// you must set echo pin on portd pin6 (ICP1)

#define US_TRIG_PORT DIO_PORTD
#define US_TRIG_PIN  DIO_PIN7

#endif /* US_CONFIG_H_ */