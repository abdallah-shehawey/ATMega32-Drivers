/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SECURITY_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : APP_Layer
 *
 */

#ifndef APP_LAYER_CONFIG_H_
#define APP_LAYER_CONFIG_H_

/* Maximum number of login attempts allowed before system lockout */
#define Tries_Max 3

/* Minimum length required for username input */
#define USERNAME_MIN_LENGTH 6

/* Minimum length required for password input */
#define PASSWORD_MIN_LENGTH 5

/* Maximum length allowed for username input */
#define USERNAME_MAX_LENGTH 15

/* Maximum length allowed for password input */
#define PASSWORD_MAX_LENGTH 20

/*
*Optoins :-
  1- CLCD_OUTPUT
  2- TERMINAL_OUTPUT
*/
#define OUTPUT_SCREEN CLCD_OUTPUT

/*
*Optoins :-
  1- KPD_INPUT
  2- TERMINAL_INPUT
*/
#define INPUT_DATA TERMINAL_INPUT

/* EEPROM Function Definitions */
/* Function to read data from specified EEPROM address */
#define EEPROM_FunReadName EEPROM_vRead

/* Function to write data to specified EEPROM address */
#define EEPROM_FunWriteName EEPROM_vWrite

/* LCD Function Definitions */
/* Function to display a string of characters on LCD */
#define CLCD_SendStringFuncName CLCD_vSendString

/* Function to display a single character on LCD */
#define CLCD_SendDataFuncName CLCD_vSendData

/* Function to clear all characters from LCD screen */
#define CLCD_ClearScreenFuncName CLCD_vClearScreen

/* Function to display integer numbers on LCD */
#define CLCD_SendIntNumberFuncName CLCD_vSendIntNumber

/* Function to set cursor position on LCD screen */
#define CLCD_SetPositionFuncName CLCD_vSetPosition

/* Function to display custom-defined characters on LCD */
#define CLCD_SendExtraCharFuncName CLCD_vSendExtraChar

/* Function to send control commands to LCD */
#define CLCD_SendCommandFuncName CLCD_vSendCommand

/* Keypad Function Definition */
/* Function to get the value of currently pressed key */
#define KPD_GetPressedFunName KPD_u8GetPressed

/* USART Function Definitions */
/* Function to receive single byte of data through USART */
#define USART_RecieveDataFuncName USART_u8ReceiveData

/* Function to send string through USART in synchronous mode */
#define USART_SendStringFuncName USART_u8SendStringSynch

/* Function to send single byte of data through USART */
#define USART_SendDataFuncName USART_u8SendData

#endif /* APP_LAYER_CONFIG_H_ */
