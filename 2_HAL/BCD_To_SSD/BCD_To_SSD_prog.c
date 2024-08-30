/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    BCD_To_SSD_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : BCD To Seven_Segments
 *
 */

#include "STD_MACROS.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "BCD_To_SSD_interface.h"
#include "BCD_To_SSD_config.h"
#include "BCD_To_SSD_private.h"

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function initialize the port which connected to 7 Seg leds as output pins ( 4 Pins or Port )
 * Parameters :
            =>Copy_u8PORT --> Port Name [ SSD_PORTA ,	SSD_PORTB , SSD_PORTC , SSD_PORTD ]
 * return : void
 */
void SSD_vInitDataPort(SSD_config Configuration)
{
  if (Configuration.Nibble == SSD_LOW_NIBBLE)
  {
    DIO_vSetLowNibbleDir(Configuration.DataPort, 0x0F);
  }
  else if (Configuration.Nibble == SSD_HIGH_NIBBLE)
  {
    DIO_vSetHighNibbleDir(Configuration.DataPort, 0x0F);
  }
}

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function write Number on 7 seg [ 0 : 9 ]
 * Parameters : => struct has the SSD type , data port and enable(port & pin)
 * return : void
 */
void SSD_vSendNumber(SSD_config Configuration, u8 Copy_u8Number)
{
  if (Configuration.Nibble == SSD_LOW_NIBBLE)
  {
    DIO_vWriteLowNibble(Configuration.DataPort, Copy_u8Number);
  }
  else if (Configuration.Nibble == SSD_HIGH_NIBBLE)
  {
    DIO_vWriteHighNibble(Configuration.DataPort, Copy_u8Number);
  }
}

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function enable common pin
 * Parameters : => struct has the SSD type , data port and enable(port & pin)
 * return : void
 */
void SSD_vEnable(SSD_config Configuration)
{
  if (Configuration.Type == SSD_COMMON_CATHODE)
  {
    DIO_enumSetPinDir   (Configuration.EnablePort, Configuration.EnablePin, DIO_HIGH);
    DIO_enumWritePinVal (Configuration.EnablePort, Configuration.EnablePin, DIO_LOW);
  }
  else if (Configuration.Type == SSD_COMMON_ANODE)
  {
    DIO_enumSetPinDir(Configuration.EnablePort, Configuration.EnablePin, DIO_HIGH);
    DIO_enumWritePinVal(Configuration.EnablePort, Configuration.EnablePin, DIO_HIGH);
  }
}

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function disable common pin
 * Parameters : => struct has the SSD type , data port and enable(port & pin)
 * return : void
 */
void SSD_vDisable(SSD_config Configuration)
{
  if (Configuration.Type == SSD_COMMON_CATHODE)
  {
    DIO_enumSetPinDir(Configuration.EnablePort, Configuration.EnablePin, DIO_HIGH);
    DIO_enumWritePinVal(Configuration.EnablePort, Configuration.EnablePin, DIO_HIGH);
  }
  else if (Configuration.Type == SSD_COMMON_ANODE)
  {
    DIO_enumSetPinDir(Configuration.EnablePort, Configuration.EnablePin, DIO_HIGH);
    DIO_enumWritePinVal(Configuration.EnablePort, Configuration.EnablePin, DIO_LOW);
  }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    END    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
