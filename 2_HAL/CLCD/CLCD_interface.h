/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    CLCD_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : CLCD
 *
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_
#include "STD_TYPES.h"

#define EIGHT_BITS                         0x38      // 8 bits mode initialization (8-bit data, 2-line display, 5 x 7 font )
#define FOUR_BITS                          0x28      // 4 bits mode initialization
#define CLCD_DISPLAYON_CURSOROFF           0x0c      // display on, cursor off, don't blink character
#define CLCD_DISPLAYOFF_CURSOROFF          0x08      // turn display off
#define CLCD_DISPLAYON_CURSORON            0x0e      // display on, cursor on, don't blink character
#define CLCD_DISPLAYON_CURSORON_BLINK      0x0f      // display on, cursor on, with blink character
#define CLCD_ClEAR                         0x01      // replace all characters with ASCII 'space'
#define CLCD_ENTRY_MODE                    0x06      // shift cursor from left to right on read/write
#define CLCD_HOME                          0x02      // return cursor to first position on first line
#define CLCD_SET_CURSOR                    0x80      // set cursor position
#define CLCD_CGRAM                         0x40      // the first Place/Address at CGRAM
#define CLCD_SHIFT_DISPLAY_RIGHT           0x1c      // shift the entire display right cursor follows the display shift
#define CLCD_SHIFT_DISPLAY_LEFT            0x18      // shift the entire display left cursor follows the display shift
#define CLCD_SHIFT_CURSOR_RIGHT            0x14      // shift the entire display right cursor follows the display shift
#define CLCD_SHIFT_CURSOR_LEFT             0x10      // shift the entire display left cursor follows the display shift

/*___________________________________________________________________________________________________________________*/

#define CLCD_ROW_1                         1
#define CLCD_ROW_2                         2

#define CLCD_COL_1                         1
#define CLCD_COL_2                         2
#define CLCD_COL_3                         3
#define CLCD_COL_4                         4
#define CLCD_COL_5                         5
#define CLCD_COL_6                         6
#define CLCD_COL_7                         7
#define CLCD_COL_8                         8
#define CLCD_COL_9                         9
#define CLCD_COL_10                        10
#define CLCD_COL_11                        11
#define CLCD_COL_12                        12
#define CLCD_COL_13                        13
#define CLCD_COL_14                        14
#define CLCD_COL_15                        15
#define CLCD_COL_16                        16

#define CLCD_HIGH_NIBBLE                   0
#define CLCD_LOW_NIBBLE                    1

/*___________________________________________________________________________________________________________________*/

void CLCD_vInit                            (void                                );
void CLCD_vSendData                        (u8 Copy_u8Data                      );
void CLCD_vSendCommand                     (u8 Copy_u8Command                   );
void CLCD_vClearScreen                     (void);
void CLCD_vSetPosition                     (u8 Copy_u8ROW, u8 Copy_u8Col        );

void CLCD_vSendString                      (const u8 *Copy_u8PrtStrign          );
void CLCD_vSendIntNumber                   (s32 Copy_s32Number                  );
void CLCD_vSendFloatNumber                 (f64 Copy_f64Number                  );

void CLCD_voidShiftDisplayRight            (void                                );
void CLCD_voidShiftDisplayLeft             (void                                );

void CLCD_vSendExtraChar                   (u8 Copy_u8Row, u8 Copy_u8Col        );

#endif /* CLCD_INTERFACE_H_ */
