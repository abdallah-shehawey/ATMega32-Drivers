/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX                   *((volatile u8 *)0x27) // ADC multiplexer selection register
/* ADMUX Bits   */
#define ADMUX_REFS1              7                     // Reference selection bit1
#define ADMUX_REFS0              6                     // Reference selection bit0
#define ADMUX_ADLAR              5                     // ADC left adjust result

/*___________________________________________________________________________________________________________________*/

#define ADCSRA                   *((volatile u8 *)0x26) // ADC control and status register A
/* ADCSRA Bits   */
#define ADCSRA_ADEN              7                      // ADC enable
#define ADCSRA_ADSC              6                      // Start conversion
#define ADCSRA_ADATE             5                      // Auto trigger enable
#define ADCSRA_ADIF              4                      // Interrupt flag
#define ADCSRA_ADIE              3                      // Interrupt enable

/*___________________________________________________________________________________________________________________*/

/* Data Reg  */
#define ADCH                     *((volatile u8  * )0x25)  // ADC high register
#define ADCL                     *((volatile u8  * )0x24)  // ADC Low register
#define ADC_DATA_RE              *((volatile u16 * )0x24) // ADC Low + High

/*___________________________________________________________________________________________________________________*/

#define SFIOR                    *((volatile u8 *)0x50)
/* SFIOR Bits   */
#define SFIOR_ADTS2              7                       // Trigger Source bit2
#define SFIOR_ADTS1              6                       // Trigger Source bit1
#define SFIOR_ADTS0              5                       // Trigger Source bit0

/*___________________________________________________________________________________________________________________*/

/* Values of the global var (ADC_u8ISRSource)  */
#define SINGLE_CHANNEL_ASYNCH   0
#define CHAIN_CHANNEL_ASYNCH    1

#endif /* ADC_private_H_ */
