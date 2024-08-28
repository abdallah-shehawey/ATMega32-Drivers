/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EEPROM_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : External EEPROM
 *
 */
 
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_vSendDataByte   (u16 Copy_u16LocationAddress, u8 Copy_u8DataByte);

void EEPROM_u8ReadDataByte  (u16 Copy_u16LocationAddress, u8 *Local_u8Data  );

#endif
