/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SW_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : SWITCH / BUTTON
 *
 */

#ifndef SW_INTERFACE_H_
#define SW_INTERFACE_H_

#define SW_PREESED               1
#define SW_NOT_PRESSED           0

#define SW_INT_PULL_UP           0
#define SW_EXT_PULL_UP           1
#define SW_EXT_PULL_DOWN         2
#define SW_FLOATTING_PULL_UP     3


typedef struct
{
  u8 PortName ;
  u8 PinNumber;
  u8 PullState;
} SW_Config;

void SW_vInit                    (SW_Config SW_Configuration);
u8   SW_u8Read                   (SW_Config SW_Configuration);

#endif /* SW_INTERFACE_H_ */
