/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXIT_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define MCUCR     *((volatile u8*) 0x55)
#define MCUCSR    *((volatile u8*) 0x54)
#define GICR      *((volatile u8*) 0x5B)
#define GIFR      *((volatile u8*) 0x5A)

#define NULL      0

#endif /* EXTI_PRIVATE_H_ */
