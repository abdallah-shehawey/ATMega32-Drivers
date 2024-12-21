/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXIT_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */

#ifndef EXTI_ITERFACE_H_
#define EXTI_ITERFACE_H_

/*
  Hint : I assume those values 6,7,5 because the possition of each INT bits in the Reg (GICR,GIFR ....)
  I will use That for SET and CLR BITS

 */

#define EXTI_LINE0               6
#define EXTI_LINE1               7
#define EXTI_LINE2               5

/*___________________________________________________________________________________________________________________*/

#define EXTI_FALLING_EDGE        0
#define EXTI_RISING_EDGE         1
#define EXTI_LOW_LEVEL           2
#define EXTI_ON_CHANGE           3

#define NULL                     0

/*___________________________________________________________________________________________________________________*/

void EXTI_vInit                  (void                                           );
void EXTI_vSetSignal             (u8 Copy_u8SenseMode, u8 Copy_u8Line            );

u8   EXTI_vDisableInterrupt      (u8 Copy_u8Line                                 );
u8   EXTI_vEnableInterrupt       (u8 Copy_u8Line                                 );

void EXTI_vClearFlag             (u8 Copy_u8Line                                 );
u8   EXTI_u8GETFlag              (u8 Copy_u8Line                                 );

u8   EXTI_vSetCallBack           (void (*Copy_pvCallBack)(void), u8 Copy_u8Line  );

#endif /* EXTI_ITERFACE_H_ */
