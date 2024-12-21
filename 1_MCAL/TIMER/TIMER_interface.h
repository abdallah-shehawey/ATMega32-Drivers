/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TIMER_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : TIMER
 *
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/* Define indexes for the global pointer to func for ISR  */

#define TIMER0_OVF_VECTOR_ID                                 11
#define TIMER0_CTC_VECTOR_ID                                 10

#define TIMER1_OVF_VECTOR_ID                                 9
#define TIMER1_CTCB_VECTOR_ID                                8
#define TIMER1_CTCA_VECTOR_ID                                7
#define TIMER1_ICU_VECTOR_ID                                 6

#define TIMER2_OVF_VECTOR_ID                                 5
#define TIMER2_CTC_VECTOR_ID                                 4

/*___________________________________________________________________________________________________________________*/

/* WDT Prescaler select  */
#define WDT_PS_MASKING                                       0b11111000
#define WDT_PS_16_3_MS                                       0
#define WDT_PS_32_5_MS                                       1
#define WDT_PS_65_MS                                         2
#define WDT_PS_0_13_S                                        3
#define WDT_PS_0_26_S                                        4
#define WDT_PS_0_52_S                                        5
#define WDT_PS_1_0_S                                         6
#define WDT_PS_2_1_S                                         7

/*___________________________________________________________________________________________________________________*/

#define DISABLE                                              0
#define ENABLE                                               1

#define FALLING_EDGE                                         0
#define RISING_EDGE                                          1

#define TIMER_NO_CLOCK_SOURCE                                0
#define TIMER_NO_PRESCALER_FACTOR                            1
#define TIMER_DIVISION_FACTOR_8                              2
#define TIMER_DIVISION_FACTOR_64                             3
#define TIMER_DIVISION_FACTOR_256                            4
#define TIMER_DIVISION_FACTOR_1024                           5
#define TIMER_T0_EXTERNAL_CLOCK_SOURCE_FALLING               6
#define TIMER_T0_EXTERNAL_CLOCK_SOURCE_RISING                7

#define TIMER2_NO_CLOCK_SOURCE                               0
#define TIMER2_NO_PRESCALER_FACTOR                           1
#define TIMER2_DIVISION_FACTOR_8                             2
#define TIMER2_DIVISION_FACTOR_32                            3
#define TIMER2_DIVISION_FACTOR_64                            4
#define TIMER2_DIVISION_FACTOR_128                           5
#define TIMER2_DIVISION_FACTOR_256                           6
#define TIMER2_DIVISION_FACTOR_1024                          7

#define TIMER_PRESCALER_MASK                                 0b11111000 /* This Value also could use for bit masking */

#define TIMER_NORMAL_MODE                                    0
#define TIMER_PWM_MODE                                       1
#define TIMER_CTC_MODE                                       2
#define TIMER_FAST_PWM_MODE                                  3

#define TIMER_OC_DISCONNECTED                                0
#define TIMER_OC_TOGGEL                                      1
#define TIMER_OC_LOW                                         2
#define TIMER_OC_HIGH                                        3

#define TIMER_OC_DISCONNECTED                                0
#define TIMER_CLR_ON_CTC_SET_ON_TOP                          2
#define TIMER_SET_ON_CTC_CLR_ON_TOP                          3

#define TIMER1_NORMAL_MODE                                   0
#define TIMER1_PWM_8_BIT_MODE                                1
#define TIMER1_PWM_9_BIT_MODE                                2
#define TIMER1_PWM_10_BIT_MODE                               3
#define TIMER1_CTC_OCR1A_MODE                                4
#define TIMER1_FAST_PWM_8_BIT_MODE                           5
#define TIMER1_FAST_PWM_9_BIT_MODE                           6
#define TIMER1_FAST_PWM_10_BIT_MODE                          7
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE          8
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE         9
#define TIMER1_PWM_PHASE_CORRECT_ICR1_MODE                   10
#define TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE                  11
#define TIMER1_CTC_ICR1_MODE                                 12
#define TIMER1_FAST_PWM_ICR1_MODE                            14
#define TIMER1_FAST_PWM_OCR1A_MODE                           15

#define TIMER_u8_ICP_FALLING_EDGE                            0
#define TIMER_u8_ICP_RAISING_EDGE                            1

/*___________________________________________________________________________________________________________________*/

/* Interface Function */
void TIMER0_vInit                  (void                                                     );
void TIMER0_vSetPreload            (u8 Copy_u8Preload                                        );
void TIMER0_vSetCTC                (u8 Copy_u8CTC                                            );
u8 TIMER0_u8GetTimerCounterValue   (void                                                     );
void Timer0_vSetPrescaler(u8 Prescaler);

void TIMER1_vInit                  (void                                                     );
void TIMER1_vSetPreload            (u16 Copy_u16Preload                                      );
void TIMER1_vSetCTCA               (u16 Copy_u16CTCA                                         );
void TIMER1_vSetCTCB               (u16 Copy_u16CTCB                                         );
void TIMER1_vSetICR1               (u16 Copy_u16ICR1                                         );
u16 TIMER1_u16GetTimerCounterValue (void                                                     );

void TIMER2_vInit                  (void                                                     );
void TIMER2_vSetPreload            (u8 Copy_u8Preload                                        );
void TIMER2_vSetCTC                (u8 Copy_u8CTC                                            );
u8 TIMER2_u8GetTimerCounterValue   (void                                                     );
void Timer2_vSetPrescaler(u8 Prescaler);

/*******************************/

void TIMER_vICUInitEnable           (void                                                    );
u8 TIMER_vICUSetTriggerEdge         (u8 Copy_u8Edge                                          );
void TIMER_vICUEnableInterrupt      (void                                                    );
void TIMER_vICUDisableInterrupt     (void                                                    );
u16 TIMER_u16GetICR                 (void                                                    );

void TIMER_vSetPWM                  (u16 Copy_u16CompareValue                                );
u8 TIMER_u8GetPWMOnPeriod           (u16 *Copy_pu16OnPeriod                                  );
u8 TIMER_u8GetPWMTotalPeriod        (u32 *Copy_pu32TotalPeriod                               );
u8 TIMER_u8GetPWMDutyCycle          (u8 *Copy_pu8DutyCycle                                   );
void TIMER_vWDTSleep                (void                                                    );
void TIMER_vWDTEnable               (void                                                    );
void TIMER_vWDTDisable              (void                                                    );

u8 TIMER_u8SetCallBack              (void (*Copy_pvCallBackFunc)(void), u8 Copy_u8VectorID   );




#endif /* TIMER_INTERFACE_H_ */
