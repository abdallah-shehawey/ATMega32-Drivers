/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     TWI_config.h      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : I2C/TWI
 *
 */
/*File Gard*/
#ifndef TWI_CONFIG_H_
#define TWI_CONFIG_H_

#define F_CPU 8000000UL
/*
$ Options :-
	1-PRESCALLER_BY_1
	2-PRESCALLER_BY_4
	3-PRESCALLER_BY_16
	4-PRESCALLER_BY_64
*/
#define TWI_PRESCALLER  PRESCALLER_BY_1

/*Set SCL frequency to 400kHz, with 8Mhz system frequency*/
#define SCL_Clock  400000UL


#endif /* TWI_CONFIG_H_ */