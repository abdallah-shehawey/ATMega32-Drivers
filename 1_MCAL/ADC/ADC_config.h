/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */

#ifndef ADC_config_H_
#define ADC_config_H_

/*
  *Option
  ==>1- ADC_EN
  ==>2- ADC_DIS
*/
#define ADC_STATUS ADC_EN

/*
 *Option:-
  ==> 1-INT_EN
  ==> 2-INT_DIS
 */

#define ADC_INT_STATUS INT_DIS

/*
 *Option:-
  ==> 1-AREF
  ==> 2-AVCC
  ==> 3-INTERNAL_2_56
 */

#define ADC_VREF AVCC

/*
  *Option :
  ==> 1-RIGHT_ADJUSTMENT
  ==> 2-LEFT_ADJUSTMENT
  */

#define ADC_ADJUSTMENT RIGHT_ADJUSTMENT

/*
  *Options:-
  ==> 1-ADC_PRE_2
  ==> 2-ADC_PRE_4
  ==> 3-ADC_PRE_8
  ==> 4-ADC_PRE_16
  ==> 5-ADC_PRE_32
  ==> 6-ADC_PRE_64
  ==> 7-ADC_PRE_128
 */

#define ADC_PRESCALLER ADC_PRE_128

/*
 *Option:-
  ==> 1-ADC_SINGLE_CONVERSION
  ==> 2-ADC_FREE_RUNNING
  ==> 3-ADC_ANALOG_COMPARATOR
  ==> 4-ADC_EXTI0
  ==> 5-ADC_TIM0_CTC
  ==> 6-ADC_TIM0_OVF
  ==> 7-ADC_TIM1_CTC_CHANNEL_B
  ==> 8-ADC_TIM1_OVF
  ==> 9-ADC_TIM1_ICU
 */
#define ADC_TRIGGERING_SOURCE ADC_SINGLE_CONVERSION

#define ADC_TIMEOUT 50000

#endif /* ADC_config_H_ */
