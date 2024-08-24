/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    KPD_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : KPD
 *
 */

#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#define NOTPRESSED  0xFF

void KPD_vInit       (void);
u8   KPD_u8GetPressed(void);

#endif /* KPD_INTERFACE_H_ */
