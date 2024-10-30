/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SECURITY_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : APP_Layer
 *
 */

#ifndef APP_LAYER_CONFIG_H_
#define APP_LAYER_CONFIG_H_

#define Tries_Max 3
#define USERNAME_MIN_LENGTH 6
#define PASSWORD_MIN_LENGTH 5

#define USERNAME_MAX_LENGTH 15
#define PASSWORD_MAX_LENGTH 20

/*
*Optoins :-
  1- CLCD_OUTPUT
  2- TERMINAL_OUTPUT
*/
#define OUTPUT_SCREEN TERMINAL_OUTPUT

/*
*Optoins :-
  1- KPD_INPUT
  2- TERMINAL_INPUT
*/
#define INPUT_DATA TERMINAL_INPUT

/* EEPROM Functions Name */
#define EEPROM_FunReadName EEPROM_vRead
#define EEPROM_FunWriteName EEPROM_vWrite

/* CLCD Functions Name */
#define CLCD_SendStringFuncName CLCD_vSendString
#define CLCD_SendDataFuncName CLCD_vSendData
#define CLCD_ClearScreenFuncName CLCD_vClearScreen
#define CLCD_SendIntNumberFuncName CLCD_vSendIntNumber
#define CLCD_SetPositionFuncName CLCD_vSetPosition
#define CLCD_SendExtraCharFuncName CLCD_vSendExtraChar
#define CLCD_SendCommandFuncName CLCD_vSendCommand

/*KPD Functions Name */
#define KPD_GetPressedFunName KPD_u8GetPressed

/* USART Functions Name */
#define USART_RecieveDataFuncName USART_u8ReceiveData
#define USART_SendStringFuncName USART_u8SendStringSynch
#define USART_SendDataFuncName USART_u8SendData

#endif /* APP_LAYER_CONFIG_H_ */
