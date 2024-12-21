/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     TWI_interface.h      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : I2C/TWI
 *
 */

/*File Gard*/
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

/* Error Status fot TWI */
typedef enum
{
	NoError                  ,
	StartConditionErr        ,
	RepeatedStartError       ,
	SlaveAddressWithWriteErr ,
	SlaveAddressWithReadErr  ,
	MasterWriteByteErr       ,
	MasterReadByteErr        ,
	SlaveWriteByteErr        ,
	SlaveReadByteErr         ,
}TWI_ErrStatus             ;

/*Set master address to 0 if master will not be addressed*/
void          TWI_vInitMaster                    (u8 Copy_u8Address                       );

void          TWI_vInitSlave                     (u8 Copy_u8Address                       );

TWI_ErrStatus TWI_SendStartCondition             (void                                    );

TWI_ErrStatus TWI_SendRepeatedStart              (void                                    );

TWI_ErrStatus TWI_SendSlaveAddressWithWrite      (u8 Copy_u8SlaveAddress                  );

TWI_ErrStatus TWI_SendSlaveAddressWithRead       (u8 Copy_u8SlaveAddress                  );

TWI_ErrStatus TWI_MasterWriteDataByte            (u8 Copy_u8DataByte                      );

TWI_ErrStatus TWI_MasterReadDataByte             (u8* Copy_pu8DataByte                    );

TWI_ErrStatus TWI_SlaveWriteDataByte             (u8 Copy_u8DataByte                      );

TWI_ErrStatus TWI_SlaveReadDataByte              (u8* Copy_pu8DataByte                    );


void          TWI_vSendStopCondition             (void                                    );


#endif /* TWI_INTERFACE_H_ */