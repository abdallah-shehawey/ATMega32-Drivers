/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EEPROM_prog.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : EEPROM
 *
 */

#include "STD_MACROS.h"
#include "STD_TYPES.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"

/*___________________________________________________________________________________________________________________*/

/*
Function Name        : EEPROM_write
Function Returns     : void
Function Arguments   : unsigned short address, unsigned char data
Function Description :  write one byte to the given  address.
*/
void EEPROM_vWrite(u16 address, u8 data)
{
  /*set up address register*/
  EEAR_REG = address;
  /*set up data register*/
  EEDR_REG = data;
  /*write logical one to EEMWE*/
  SET_BIT(EECR_REG, EECR_EEMWE);
  /*start EEPROM write by setting EEWE*/
  SET_BIT(EECR_REG, EECR_EEWE );
  /* wait for completion of  write operation*/
  while (READ_BIT(EECR_REG, EECR_EEWE) == 1);
}

/*___________________________________________________________________________________________________________________*/

/*
Function Name        : EEPROM_read
Function Returns     : unsigned char
Function Arguments   :  unsigned short address
Function Description :  read one byte from the given  address.
*/
u8 EEPROM_vRead(u16 address)
{
  /*set up address register*/
  EEARL_REG = (char)address;
  EEARH_REG = (char)(address >> 8);
  /*start EEPROM read by setting EERE*/
  SET_BIT(EECR_REG, EECR_EERE);
  /*return data from data register*/
  return EEDR_REG;
}