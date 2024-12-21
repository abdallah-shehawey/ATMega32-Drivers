/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SECURITY_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : APP_Layer
 *
 */
#ifndef APP_LAYER_SECURITY_H_
#define APP_LAYER_SECURITY_H_

#define CLCD_OUTPUT                       1
#define TERMINAL_OUTPUT                   2

#define KPD_INPUT                         1
#define TERMINAL_INPUT                    2

#define NOTPRESSED                        0xFF

#define EEPROM_UserNameStatus             0x10
#define EEPROM_PassWordStatus             0x11
#define EEPROM_NoTries_Location           0x12
#define EEPROM_USNL_Location              0x13
#define EEPROM_PWL_Location               0x14

#define EEPROM_UserNameStartLocation      0x21
#define EEPROM_UserNameEndLocation        0x40

#define EEPROM_PassWordStartLocation      0x41
#define EEPROM_PassWordEndLocation        0x60

void UserName_Set                         (void);
void PassWord_Set                         (void);
void UserName_Check                       (void);
void PassWord_Check                       (void);
void Sign_In                              (void);
void Error_TimeOut                        (void);
void EEPROM_vInit                         (void);

#if OUTPUT_SCREEN == CLCD_OUTPUT
void Clear_Char();
#endif

#endif /* APP_LAYER_SECURITY_H_ */
