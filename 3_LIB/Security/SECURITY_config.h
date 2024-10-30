/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SECURITY_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : APP_Layer
 *
 */

#ifndef APP_LAYER_CONFIG_H_
#define APP_LAYER_CONFIG_H_


#define Tries_Max           3
#define USERNAME_MIN_LENGTH 7
#define PASSWORD_MIN_LENGTH 5

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
#define INPUT_DATA    KPD_INPUT

#endif /* APP_LAYER_CONFIG_H_ */
