/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SECURITY_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : APP_Layer
 *
 */
#ifndef APP_LAYER_SECURITY_H_
#define APP_LAYER_SECURITY_H_

#define CLCD_OUTPUT 1
#define TERMINAL_OUTPUT 2

#define KPD_INPUT 1
#define TERMINAL_INPUT 2

#define NOTPRESSED 0xFF

#define EEPROM_UserNameStatus 0x10
#define EEPROM_PassWordStatus 0x11
#define EEPROM_NoTries_Location 0x12
#define EEPROM_USNL_Location 0x13
#define EEPROM_PWL_Location 0x14

#define EEPROM_UserNameStartLocation 0x21
#define EEPROM_UserNameEndLocation 0x40

#define EEPROM_PassWordStartLocation 0x41
#define EEPROM_PassWordEndLocation 0x60

/* Function Declarations */

/**
 * @brief   Sets up a new username with input validation
 * @details Prompts user to enter username, validates length requirements,
 *          and stores it in EEPROM if valid
 */
void UserName_Set(void);

/**
 * @brief   Sets up a new password with input validation
 * @details Prompts user to enter password, validates length requirements,
 *          and stores it in EEPROM if valid
 */
void PassWord_Set(void);

/**
 * @brief   Validates entered username against stored credentials
 * @details Compares user input with username stored in EEPROM
 *          Sets UserName_Check_Flag to indicate validation result
 */
void UserName_Check(void);

/**
 * @brief   Validates entered password against stored credentials
 * @details Compares user input with password stored in EEPROM
 *          Sets PassWord_Check_Flag to indicate validation result
 */
void PassWord_Check(void);

/**
 * @brief   Handles the complete login process
 * @details Manages username/password validation, tracks login attempts,
 *          and handles timeout on excessive failed attempts
 */
void Sign_In(void);

/**
 * @brief Implements timeout after maximum failed login attempts
 * @details Shows countdown timer and resets attempt counter after timeout
 */
void Error_TimeOut(void);

/**
 * @brief   Initializes security system from EEPROM state
 * @details Reads stored credentials and system state from EEPROM
 *          Handles first-time setup if no credentials exist
 */
void EEPROM_vInit(void);

#if OUTPUT_SCREEN == CLCD_OUTPUT
/**
 * @brief Helper function to clear a character from LCD display
 * @details Moves cursor left, writes space, moves cursor left again
 */
void Clear_Char(void);
#endif

#endif /* APP_LAYER_SECURITY_H_ */
