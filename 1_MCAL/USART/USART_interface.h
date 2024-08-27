/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    USART_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : MCAL
 *  SWC    : USART
 *
 */

/*File Gard*/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#define USART_1X			                      1
#define USART_2X			                      2

#define ASYNCHRONOUS		                    1
#define SYNCHRONOUS 		                    0

#define EVEN_PARITY			                    0
#define ODD_PARITY 			                    1

#define STOP_BIT_1			                    0
#define STOP_BIT_2			                    1

#define DATA_SIZE_5_BIT		                  0
#define DATA_SIZE_6_BIT		                  1
#define DATA_SIZE_7_BIT		                  2
#define DATA_SIZE_8_BIT		                  3
#define DATA_SIZE_9_BIT		                  4

#define XCK_RISING_TX_XCH_FALLING_RX			  0
#define XCK_RISING_RX_XCH_FALLING_TX			  1


void USART_vInit                            (void                                                                          );
u8   USART_u8SendData                       (u8 Copy_u8Data                                                                );
u8   USART_u8ReceiveData                    (u8 * Copy_u8ReceivedData                                                      );
u8   USART_u8GetParityError                 (void                                                                          );

u8   USART_u8SendStringSynch                ( u8 * Copy_pu8String                                                          );
u8   USART_u8SendStringAsynch               ( u8 * Copy_pu8String , void (* NotificationFunc)(void)                        );

u8   USART_u8ReceiveBufferSynch             (u8 * Copy_pu8String , u32 Copy_u32BufferSize                                  );
u8   USART_u8ReceiveBufferAsynch            (u8 * Copy_pu8String , u32 Copy_u32BufferSize , void (* NotificationFunc)(void));

#endif /* USART_INTERFACE_H_ */
