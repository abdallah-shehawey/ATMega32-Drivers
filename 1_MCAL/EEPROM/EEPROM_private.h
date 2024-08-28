/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EEPROM_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : EEPROM
 *
 */
#ifndef EEPROM_PRIVATE_H_
#define EEPROM_PRIVATE_H_

/* EEPROM Data Register */
#define EEDR_REG   *((volatile u8 *)0x3D)
/* EEPROM Address Register */
#define EEAR_REG    *((volatile u16 *)0x3E )
#define EEARL_REG   *((volatile u8  *)0x3E )
#define EEARH_REG   *((volatile u8  *)0x3F )

/* EEPROM Control Register */
#define EECR_REG    *((volatile u8  *)0x3C )
#define EECR_EERE   0
#define EECR_EEWE   1
#define EECR_EEMWE  2
#define EECR_EERIE  3

#endif /* EEPROM_PRIVATE_H_ */
