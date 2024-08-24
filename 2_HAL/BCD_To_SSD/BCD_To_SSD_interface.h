/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SSD_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : BCD To Seven_Segments
 *
 */

#ifndef BCD_To_SSD_INTERFACE_H_
#define BCD_To_SSD_INTERFACE_H_

#define SSD_COMMON_CATHODE   0
#define SSD_COMMON_ANODE     1

#define SSD_LOW_NIBBLE       0
#define SSD_HIGH_NIBBLE      1

/*PORT Defines*/
#define SSD_PORTA            0
#define SSD_PORTB            1
#define SSD_PORTC            2
#define SSD_PORTD            3

/*PIN Defines*/
#define SSD_PIN0             0
#define SSD_PIN1             1
#define SSD_PIN2             2
#define SSD_PIN3             3
#define SSD_PIN4             4
#define SSD_PIN5             5
#define SSD_PIN6             6
#define SSD_PIN7             7
#define SSD_PIN8             8

typedef struct
{
  u8 Type       ;   // SSD_COMMON_CATHODE or SSD_COMMON_ANODE
  u8 DataPort   ;   // SSD_PORTA or SSD_PORTB or SSD_PORTC or SSD_PORTD
  u8 EnablePort ;   // SSD_PORTA or SSD_PORTB or SSD_PORTC or SSD_PORTD
  u8 EnablePin  ;   // SSD_PIN0, SSD_PIN1, SSD_PIN2, SSD_PIN3, SSD_PIN4, SSD_PIN5, SSD_PIN6, SSD_PIN7
  u8 Nibble     ;   // SSD Connected to LOW NIBBLE or HIGH NIBBLE
} SSD_config;

void SSD_vInitDataPort   (SSD_config Configuration);
void SSD_vSendNumber     (SSD_config Configuration, u8 Copy_u8Number);
void SSD_vEnable         (SSD_config Configuration);
void SSD_vDisable        (SSD_config Configuration);

#endif /* SSD_INTERFACE_H_ */
