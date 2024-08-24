/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    US_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : Ultra Sonic
 *
 */

#ifndef US_INTERFACE_H_
#define US_INTERFACE_H_

#include "STD_TYPES.h"

void US_vInit       (void);
u8 US_u8ReadDistance(void);

#endif /* US_INTERFACE_H_ */
