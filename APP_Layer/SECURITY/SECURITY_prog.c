/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SECURITY_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : APP_Layer
 *  Security system implementation for ATMega32 with EEPROM-based credential storage
 */

#include <util/delay.h>

#include "../STD_TYPES.h"
#include "../STD_MACROS.h"

#include "SECURITY_config.h"
#include "SECURITY_interface.h"

#include "../../MCAL_Layer/DIO/DIO_interface.h"
#include "../../MCAL_Layer/EEPROM/EEPROM_interface.h"

#if OUTPUT_SCREEN == CLCD_OUTPUT
#if INPUT_DATA == KPD_INPUT
#include "../../HAL_Layer/KPD/KPD_interface.h"
#include "../../HAL_Layer/CLCD/CLCD_interface.h"
#elif INPUT_DATA == TERMINAL_INPUT
#include "../../MCAL_Layer/USART/USART_interface.h"
#include "../../HAL_Layer/CLCD/CLCD_interface.h"
#endif
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
#if INPUT_DATA == KPD_INPUT
#include "../../HAL_Layer/KPD/KPD_interface.h"
#include "../../MCAL_Layer/USART/USART_interface.h"
#elif INPUT_DATA == TERMINAL_INPUT
#include "../../MCAL_Layer/USART/USART_interface.h"
#endif
#endif

/*To get Username And Password Length from number of input */
volatile u8 UserName_Length = 0, PassWord_Length = 0;
/* to Know Number Of Tries */
volatile u8 Tries = Tries_Max;

/*To get from user and compare it with saved in EEPROM in Check Function */
volatile u8 Check[21];
/* to get if User Name or Password is true and false it is default is true */
volatile u8 UserName_Check_Flag = 1, PassWord_Check_Flag = 1;
/* to get bottom from usart and error status */
volatile u8 KPD_Press, Error_State = 1;
volatile u8 UserName[20];

/**
 * @brief Initializes the security system from EEPROM state
 * @details
 * - Reads username and password lengths from EEPROM
 * - Checks remaining login attempts
 * - Handles first-time setup if no credentials exist
 * - Loads username into memory for quick access
 * - Triggers timeout if attempts were exhausted in previous session
 */
void EEPROM_vInit(void)
{
  /* To get Number of User Name and Password Length from EEPROM for second sign in */
  UserName_Length = EEPROM_FunReadName(EEPROM_USNL_Location);
  PassWord_Length = EEPROM_FunReadName(EEPROM_PWL_Location);

  /* To get number of tries left from EEPROM if it lost one of it Maximum */
  if (EEPROM_FunReadName(EEPROM_NoTries_Location) != NOTPRESSED)
  {
    Tries = EEPROM_FunReadName(EEPROM_NoTries_Location);
  }
  else
  {
  }
  /* check if There is UserName or Not */
  if (EEPROM_FunReadName(EEPROM_UserNameStatus) == NOTPRESSED)
  {
#if OUTPUT_SCREEN == CLCD_OUTPUT
    CLCD_SendStringFuncName("Please Sign Up");
    _delay_ms(500);
    CLCD_ClearScreenFuncName();
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
    // if No User Name --> Set New User Name
    USART_SendStringFuncName("Please Sign Up");
    USART_SendDataFuncName(0X0D);
#endif
    // Go To function To Set User_Name
    UserName_Set();
  }
  // And also for Password
  if (EEPROM_FunReadName(EEPROM_PassWordStatus) == NOTPRESSED)
  {
    // Go To function To Set PassWord
    PassWord_Set();
#if OUTPUT_SCREEN == CLCD_OUTPUT
    CLCD_ClearScreenFuncName();
    CLCD_SendStringFuncName("Saved Successfully");
    _delay_ms(700);
    CLCD_ClearScreenFuncName();
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
    USART_SendStringFuncName("Saved Successfully");
    USART_SendDataFuncName(0X0D);
#endif
  }
  /*___________________________________________________________________________________________________________________*/
  // check if Tries is lost or not (when user close project and reopen it when he was in time out)
  if (Tries == 0)
  {
    Error_TimeOut();
  }
  else
  {
  }
  u8 i;
  for (i = 0; i < UserName_Length; i++)
  {
    UserName[i] = EEPROM_FunReadName(EEPROM_UserNameStartLocation + i);
  }
}

//======================================================================================================================================//

/**
 * @brief Sets up a new username with input validation
 * @details
 * - Displays username creation interface
 * - Enforces minimum and maximum length requirements
 * - Handles backspace and enter key inputs
 * - Stores valid username in EEPROM
 * - Provides feedback for invalid entries
 */
void UserName_Set(void)
{
#if OUTPUT_SCREEN == CLCD_OUTPUT
  CLCD_ClearScreenFuncName();
  CLCD_SetPositionFuncName(1, 5);
  CLCD_SendStringFuncName("Set UserName");
  CLCD_SetPositionFuncName(2, 1);
  CLCD_SendStringFuncName("Maximum char : ");
  CLCD_SendIntNumberFuncName(USERNAME_MAX_LENGTH);
  CLCD_SendExtraCharFuncName(4, 15); // To Send Enter Symbol
  CLCD_SetPositionFuncName(4, 16);
  CLCD_SendStringFuncName(" : OK");
  // To start the line where i write the user name
  CLCD_SetPositionFuncName(3, 1);
  CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSORON);

#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
  USART_SendStringFuncName("Set UserName");
  USART_SendDataFuncName(0X0D);
  USART_SendStringFuncName("Maximum char : ");
  USART_SendDataFuncName((USERNAME_MAX_LENGTH / 10) + 48);
  USART_SendDataFuncName((USERNAME_MAX_LENGTH % 10) + 48);
  USART_SendDataFuncName(0X0D);
#endif

  UserName_Length = 0;
  /*Get username from user*/
  // do while with check to make user enter user name length more than 5 char
  do
  {
    // if username is less than 5 char and User Write any thing
    if (UserName_Length != 0)
    {
#if OUTPUT_SCREEN == CLCD_OUTPUT
      CLCD_ClearScreenFuncName();
      CLCD_SendStringFuncName("UserName Must be");
      CLCD_SetPositionFuncName(2, 1);
      CLCD_SendStringFuncName("More than ");
      CLCD_SendDataFuncName((USERNAME_MIN_LENGTH - 1) + 48);
      CLCD_SendStringFuncName(" Char");
      CLCD_SendExtraCharFuncName(4, 1);
      CLCD_SetPositionFuncName(4, 2);
      CLCD_SendStringFuncName(" : Exit");
      while (1)
      {
#if INPUT_DATA == KPD_INPUT
        KPD_Press = KPD_GetPressedFunName();
        if (KPD_Press != NOTPRESSED)
        {
          if (KPD_Press == '=')
          {
            break;
          }
        }
#elif INPUT_DATA == TERMINAL_INPUT
        // wait in error page until press enter
        Error_State = USART_RecieveDataFuncName(&KPD_Press);
        if (Error_State == OK)
        {
          if (KPD_Press == 0x0D || KPD_Press == 0x0F)
          {
            break;
          }
        }
#endif
      }
      CLCD_ClearScreenFuncName();
      CLCD_SetPositionFuncName(1, 3);
      CLCD_SendStringFuncName("Re Set UserName");
      CLCD_SetPositionFuncName(2, 1);
      CLCD_SendStringFuncName("Maximum char : ");
      CLCD_SendIntNumberFuncName(USERNAME_MAX_LENGTH);
      CLCD_SendExtraCharFuncName(4, 15); // To Send Enter Symbol
      CLCD_SetPositionFuncName(4, 16);
      CLCD_SendStringFuncName(" : OK");
      CLCD_SetPositionFuncName(3, 1);

#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
      USART_SendStringFuncName("UserName Must be More than ");
      USART_SendDataFuncName((USERNAME_MIN_LENGTH - 1) + 48);
      USART_SendStringFuncName(" Char");
      USART_SendDataFuncName(0X0D);
      USART_SendStringFuncName("Re Enter UserName");
      USART_SendDataFuncName(0X0D);
#endif
      UserName_Length = 0;
    }
    // get user name from user by using Keypoard
    while (1)
    {
#if INPUT_DATA == KPD_INPUT
      // get input from KPD
      KPD_Press = KPD_GetPressedFunName();
      // if user name length is valid
      // To prevent user from delete or make any thing else writing if username less is still zero and that mean user didnt write any thing
      if (KPD_Press != NOTPRESSED && UserName_Length == 0)
      {
        // if user press enter
        if (KPD_Press == '=')
        {
        }
        // if user press back space
        else if (KPD_Press == '*')
        {
        }
        else
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendDataFuncName(KPD_Press);
#endif
          EEPROM_FunWriteName(EEPROM_UserNameStartLocation + UserName_Length, KPD_Press);
          UserName_Length++;
        }
      }
      // if UserName length is less than 20 user can write and enter and do any thing
      else if (KPD_Press != NOTPRESSED && UserName_Length < USERNAME_MAX_LENGTH)
      {
        // if user press enter
        if (KPD_Press == '=')
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
          break;
        }
        // if user press back space
        else if (KPD_Press == '*')
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          Clear_Char();
#endif
          UserName_Length--;
        }
        else
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendDataFuncName(KPD_Press);
#endif
          EEPROM_FunWriteName(EEPROM_UserNameStartLocation + UserName_Length, KPD_Press);
          UserName_Length++;
        }
      }
      // if user name length is more than 20 do no thing exept enter and delete
      else if (KPD_Press != NOTPRESSED && UserName_Length >= USERNAME_MAX_LENGTH)
      {
        if (KPD_Press == '=')
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
          break;
        }
        else if (KPD_Press == '*')
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          Clear_Char();
#endif
          UserName_Length--;
        }
        else
        {
        }
      }
      else
      {
      }
#elif INPUT_DATA == TERMINAL_INPUT
      // get input from Laptop
      Error_State = USART_RecieveDataFuncName(&KPD_Press);
      // if user name length is valid
      // To prevent user from delete or make any thing else writing if username less is still zero and that mean user didnt write any thing
      if (Error_State == OK && UserName_Length == 0)
      {
        // if user press enter
        if (KPD_Press == 0x0D || KPD_Press == 0x0F)
        {
        }
        // if user press back space
        else if (KPD_Press == 0x08)
        {
        }
        else
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendDataFuncName(KPD_Press);
#endif
          EEPROM_FunWriteName(EEPROM_UserNameStartLocation + UserName_Length, KPD_Press);
          UserName_Length++;
        }
      }
      // if UserName length is less than 20 user can write and enter and do any thing
      else if (Error_State == OK && UserName_Length < USERNAME_MAX_LENGTH)
      {
        // if user press enter
        if (KPD_Press == 0x0D || KPD_Press == 0x0F)
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
          break;
        }
        // if user press back space
        else if (KPD_Press == 0x08)
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          Clear_Char();
#endif
          UserName_Length--;
        }
        else
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendDataFuncName(KPD_Press);
#endif
          EEPROM_FunWriteName(EEPROM_UserNameStartLocation + UserName_Length, KPD_Press);
          UserName_Length++;
        }
      }
      // if user name length is more than 20 do no thing exept enter and delete
      else if (Error_State == OK && UserName_Length >= USERNAME_MAX_LENGTH)
      {
        if (KPD_Press == 0x0D || KPD_Press == 0x0F)
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
          break;
        }
        else if (KPD_Press == 0x08)
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          Clear_Char();
#endif
          UserName_Length--;
        }
        else
        {
        }
      }
      else
      {
      }
#endif
    }
  } while (UserName_Length < USERNAME_MIN_LENGTH); // didn't went out untill user enter more than 5 char
  /*___________________________________________________________________________________________________________________*/

  // To write User Name length in EEPROM to dont lose it in the future and i want it in checking
  EEPROM_FunWriteName(EEPROM_UserNameStatus, 0x00);
  EEPROM_FunWriteName(EEPROM_USNL_Location, UserName_Length);
  for (u8 i = 0; i < UserName_Length; i++)
  {
    UserName[i] = EEPROM_FunReadName(EEPROM_UserNameStartLocation + i);
  }
  UserName[UserName_Length] = '\0';
}

//======================================================================================================================================//

/**
 * @brief Sets up a new password with input validation
 * @details
 * - Displays password creation interface
 * - Enforces minimum and maximum length requirements
 * - Handles backspace and enter key inputs
 * - Stores valid password in EEPROM
 * - Provides feedback for invalid entries
 */
void PassWord_Set(void)
{
  // Function to get password from user like UserName Set Function
#if OUTPUT_SCREEN == CLCD_OUTPUT
  CLCD_ClearScreenFuncName();
  CLCD_SendStringFuncName("Set PassWord");
  CLCD_SetPositionFuncName(2, 1);
  CLCD_SendStringFuncName("Maximum char : ");
  CLCD_SendIntNumberFuncName(PASSWORD_MAX_LENGTH);
  CLCD_SendExtraCharFuncName(4, 15); // To Send Enter Symbol
  CLCD_SetPositionFuncName(4, 16);
  CLCD_SendStringFuncName(" : OK");
  CLCD_SetPositionFuncName(3, 1);

#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
  USART_SendStringFuncName("Set PassWord");
  USART_SendDataFuncName(0X0D);
  USART_SendStringFuncName("Maximum char : ");
  USART_SendDataFuncName((PASSWORD_MAX_LENGTH / 10) + 48);
  USART_SendDataFuncName((PASSWORD_MAX_LENGTH % 10) + 48);
  USART_SendDataFuncName(0X0D);
#endif

  PassWord_Length = 0;
  /*Get username from user*/
  do
  {
    // if username is less than 5 char
    if (PassWord_Length != 0)
    {
#if OUTPUT_SCREEN == CLCD_OUTPUT
      CLCD_ClearScreenFuncName();
      CLCD_SendStringFuncName("PassWord Must be");
      CLCD_SetPositionFuncName(2, 1);
      CLCD_SendStringFuncName("More than ");
      CLCD_SendDataFuncName((PASSWORD_MIN_LENGTH - 1) + 48);
      CLCD_SendStringFuncName(" Char");
      CLCD_SendExtraCharFuncName(4, 1);
      CLCD_SetPositionFuncName(4, 2);
      CLCD_SendStringFuncName(" : Exit");
      while (1)
      {
#if INPUT_DATA == KPD_INPUT
        KPD_Press = KPD_GetPressedFunName();
        if (KPD_Press != NOTPRESSED)
        {
          if (KPD_Press == '=')
          {
            break;
          }
        }
#elif INPUT_DATA == TERMINAL_INPUT
        // wait in error page until press enter
        Error_State = USART_RecieveDataFuncName(&KPD_Press);
        if (Error_State == OK)
        {
          if (KPD_Press == 0x0D || KPD_Press == 0x0F)
          {
            break;
          }
        }
#endif
      }
      CLCD_ClearScreenFuncName();
      CLCD_SetPositionFuncName(1, 5);
      CLCD_SendStringFuncName("Set PassWord");
      CLCD_SetPositionFuncName(2, 1);
      CLCD_SendStringFuncName("Maximum char : ");
      CLCD_SendIntNumberFuncName(PASSWORD_MAX_LENGTH);
      CLCD_SendExtraCharFuncName(4, 15); // To Send Enter Symbol
      CLCD_SetPositionFuncName(4, 16);
      CLCD_SendStringFuncName(" : OK");
      CLCD_SetPositionFuncName(3, 1);
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
      USART_SendStringFuncName("PassWord Must be More than ");
      USART_SendDataFuncName((PASSWORD_MIN_LENGTH - 1) + 48);
      USART_SendStringFuncName(" Char");
      USART_SendDataFuncName(0X0D);

      USART_SendStringFuncName("Re Set PassWord");
      USART_SendDataFuncName(0X0D);
      USART_SendStringFuncName("Maximum char : ");
      USART_SendDataFuncName((PASSWORD_MAX_LENGTH / 10) + 48);
      USART_SendDataFuncName((PASSWORD_MAX_LENGTH % 10) + 48);
      USART_SendDataFuncName(0X0D);
#endif
      PassWord_Length = 0;
    }
#if OUTPUT_SCREEN == CLCD_OUTPUT
    CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSORON);
#endif

    // get user name from user by using Keypoard
    while (1)
    {
#if INPUT_DATA == KPD_INPUT
      // get input from Laptop
      KPD_Press = KPD_GetPressedFunName();
      // if user name length is valid
      // To prevent user from delete or make any thing else writing if username less is still zero and that mean user didnt write any thing
      if (KPD_Press != NOTPRESSED && PassWord_Length == 0)
      {
        // if user press enter
        if (KPD_Press == '=')
        {
        }
        // if user press back space
        else if (KPD_Press == '*')
        {
        }
        else
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendDataFuncName(KPD_Press);
#endif
          EEPROM_FunWriteName(EEPROM_PassWordStartLocation + PassWord_Length, KPD_Press);
          PassWord_Length++;
        }
      }
      // if UserName length is less than 20 user can write and enter and do any thing
      else if (KPD_Press != NOTPRESSED && PassWord_Length < PASSWORD_MAX_LENGTH)
      {
        // if user press enter
        if (KPD_Press == '=')
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
          break;
        }
        // if user press back space
        else if (KPD_Press == '*')
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          Clear_Char();
#endif
          PassWord_Length--;
        }
        // if user enter valid data
        else
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendDataFuncName(KPD_Press);
#endif
          EEPROM_FunWriteName(EEPROM_PassWordStartLocation + PassWord_Length, KPD_Press);
          PassWord_Length++;
        }
      }
      // if user name length is more than 20 do no thing exept enter and delete
      else if (KPD_Press != NOTPRESSED && PassWord_Length >= PASSWORD_MAX_LENGTH)
      {
        // if user press enter
        if (KPD_Press == '=')
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
          break;
        }
        // if user press back space
        else if (KPD_Press == '*')
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          Clear_Char();
#endif
          PassWord_Length--;
        }
        // if enter valid do no thing because you skipped valid char you must input
        else
        {
        }
      }
      else
      {
      }
#elif INPUT_DATA == TERMINAL_INPUT
      // get input from Laptop
      Error_State = USART_RecieveDataFuncName(&KPD_Press);
      // if user name length is valid
      // To prevent user from delete or make any thing else writing if username less is still zero and that mean user didnt write any thing
      if (Error_State == OK && PassWord_Length == 0)
      {
        // if user press enter
        if (KPD_Press == 0x0D || KPD_Press == 0x0F)
        {
        }
        // if user press back space
        else if (KPD_Press == 0x08)
        {
        }
        else
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendDataFuncName(KPD_Press);
#endif
          EEPROM_FunWriteName(EEPROM_PassWordStartLocation + PassWord_Length, KPD_Press);
          PassWord_Length++;
        }
      }
      // if UserName length is less than 20 user can write and enter and do any thing
      else if (Error_State == OK && PassWord_Length < PASSWORD_MAX_LENGTH)
      {
        // if user press enter
        if (KPD_Press == 0x0D || KPD_Press == 0x0F)
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
          break;
        }
        // if user press back space
        else if (KPD_Press == 0x08)
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          Clear_Char();
#endif
          PassWord_Length--;
        }
        // if user enter valid data
        else
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendDataFuncName(KPD_Press);
#endif
          EEPROM_FunWriteName(EEPROM_PassWordStartLocation + PassWord_Length, KPD_Press);
          PassWord_Length++;
        }
      }
      // if user name length is more than 20 do no thing exept enter and delete
      else if (Error_State == OK && PassWord_Length >= PASSWORD_MAX_LENGTH)
      {
        // if user press enter
        if (KPD_Press == 0x0D || KPD_Press == 0x0F)
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
          break;
        }
        // if user press back space
        else if (KPD_Press == 0x08)
        {
#if OUTPUT_SCREEN == CLCD_OUTPUT
          Clear_Char();
#endif
          PassWord_Length--;
        }
        // if enter valid do no thing because you skipped valid char you must input
        else
        {
        }
      }
      else
      {
      }
#endif
    }
  } while (PassWord_Length < PASSWORD_MIN_LENGTH);
  /*___________________________________________________________________________________________________________________*/

  // To write passWord length in EEPROM to dont lose it in the future and i want it in checking
  EEPROM_FunWriteName(EEPROM_PassWordStatus, 0x00);
  EEPROM_FunWriteName(EEPROM_PWL_Location, PassWord_Length);
}

//======================================================================================================================================//

/**
 * @brief Validates entered username against stored credentials
 * @details
 * - Prompts for username input
 * - Compares input length with stored length
 * - Performs character-by-character comparison
 * - Sets UserName_Check_Flag to indicate result
 * - Handles special key inputs (backspace/enter)
 */
void UserName_Check(void)
{
#if OUTPUT_SCREEN == CLCD_OUTPUT
  CLCD_ClearScreenFuncName();
  CLCD_SendStringFuncName("Check UserName");
  CLCD_SetPositionFuncName(2, 1);
  CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSORON);
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
  USART_SendStringFuncName("Check UserName");
  USART_SendDataFuncName(0X0D);
#endif
  u8 CheckLength = 0;
  UserName_Check_Flag = 1;
  while (1)
  {
#if INPUT_DATA == KPD_INPUT
    KPD_Press = KPD_GetPressedFunName();
    // if user name length is valid
    if (KPD_Press != NOTPRESSED && CheckLength == 0)
    {
      // if user press enter
      if (KPD_Press == '=')
      {
      }
      // if user press back space
      else if (KPD_Press == '*')
      {
      }
      // if user enter valid data
      else
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendDataFuncName(KPD_Press);
#endif
        Check[CheckLength] = KPD_Press;
        CheckLength++;
      }
    }
    else if (KPD_Press != NOTPRESSED && CheckLength < USERNAME_MAX_LENGTH)
    {
      // if user press enter
      if (KPD_Press == '=')
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
        break;
      }
      // if user press back space
      else if (KPD_Press == '*')
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        Clear_Char();
#endif
        CheckLength--;
      }
      // if user enter valid data
      else
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendDataFuncName(KPD_Press);
#endif
        Check[CheckLength] = KPD_Press;
        CheckLength++;
      }
    }
    // if user name length is more than 20 do no thing exept enter and delete
    else if (KPD_Press != NOTPRESSED && CheckLength >= USERNAME_MAX_LENGTH)
    {
      // if user press enter
      if (KPD_Press == '=')
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
        break;
      }
      // if user press back space
      else if (KPD_Press == '*')
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        Clear_Char();
#endif
        CheckLength--;
      }
      // if user enter valid data
      else
      {
      }
    }
    else
    {
    }
#elif INPUT_DATA == TERMINAL_INPUT
    Error_State = USART_RecieveDataFuncName(&KPD_Press);
    // if user name length is valid
    if (Error_State == OK && CheckLength == 0)
    {
      // if user press enter
      if (KPD_Press == 0x0D || KPD_Press == 0x0F)
      {
      }
      // if user press back space
      else if (KPD_Press == 0x08)
      {
      }
      // if user enter valid data
      else
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendDataFuncName(KPD_Press);
#endif
        Check[CheckLength] = KPD_Press;
        CheckLength++;
      }
    }
    else if (Error_State == OK && CheckLength < USERNAME_MAX_LENGTH)
    {
      // if user press enter
      if (KPD_Press == 0x0D || KPD_Press == 0x0F)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
        break;
      }
      // if user press back space
      else if (KPD_Press == 0x08)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        Clear_Char();
#endif
        CheckLength--;
      }
      // if user enter valid data
      else
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendDataFuncName(KPD_Press);
#endif
        Check[CheckLength] = KPD_Press;
        CheckLength++;
      }
    }
    // if user name length is more than 20 do no thing exept enter and delete
    else if (Error_State == OK && CheckLength >= USERNAME_MAX_LENGTH)
    {
      // if user press enter
      if (KPD_Press == 0x0D || KPD_Press == 0x0F)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
        break;
      }
      // if user press back space
      else if (KPD_Press == 0x08)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        Clear_Char();
#endif
        CheckLength--;
      }
      // if user enter valid data
      else
      {
      }
    }
    else
    {
    }
#endif
  }

  /*___________________________________________________________________________________________________________________*/

  // Check if UserName is correct or not
  if (CheckLength == UserName_Length)
  {
    for (u8 i = 0; i <= PassWord_Length; i++)
    {
      if (Check[i] == '\0')
      {
        break;
      }
      else if (Check[i] != EEPROM_FunReadName(EEPROM_UserNameStartLocation + i))
      {
        UserName_Check_Flag = 0; // if it false make this flag to zero
      }
      else
      {
      }
    }
  }
  else if (CheckLength != UserName_Length)
  {
    UserName_Check_Flag = 0; // and if CheckLength is != username length make it false without checkin because it fale with out checking
  }
  else
  {
  }
}

//======================================================================================================================================//

/**
 * @brief Validates entered password against stored credentials
 * @details
 * - Prompts for password input
 * - Compares input length with stored length
 * - Performs character-by-character comparison
 * - Sets PassWord_Check_Flag to indicate result
 * - Handles special key inputs (backspace/enter)
 */
void PassWord_Check(void)
{
#if OUTPUT_SCREEN == CLCD_OUTPUT
  CLCD_ClearScreenFuncName();
  CLCD_SendStringFuncName("Check PassWord");
  CLCD_SetPositionFuncName(2, 1);
  CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSORON);
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
  USART_SendStringFuncName("Check PassWord");
  USART_SendDataFuncName(0X0D);
#endif
  u8 CheckLength = 0;
  PassWord_Check_Flag = 1;

  while (1)
  {
#if INPUT_DATA == KPD_INPUT
    KPD_Press = KPD_GetPressedFunName();
    // if user name length is valid
    if (KPD_Press != NOTPRESSED && CheckLength == 0)
    {
      // if user press enter
      if (KPD_Press == '=')
      {
      }
      // if user press back space
      else if (KPD_Press == '*')
      {
      }
      // if user enter valid data
      else
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendDataFuncName(KPD_Press);
#endif
        Check[CheckLength] = KPD_Press;
        CheckLength++;
      }
    }
    else if (KPD_Press != NOTPRESSED && CheckLength < PASSWORD_MAX_LENGTH)
    {
      if (KPD_Press == '=')
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
        break;
      }
      else if (KPD_Press == '*')
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        Clear_Char();
#endif
        CheckLength--;
      }
      else
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendDataFuncName(KPD_Press);
#endif
        Check[CheckLength] = KPD_Press;
        CheckLength++;
      }
    }
    // if user name length is more than 20 do no thing exept enter and delete
    else if (KPD_Press != NOTPRESSED && CheckLength >= PASSWORD_MAX_LENGTH)
    {
      if (KPD_Press == '=')
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
        break;
      }
      else if (KPD_Press == '*')
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        Clear_Char();
#endif
        CheckLength--;
      }

      else
      {
      }
    }
    else
    {
    }
#elif INPUT_DATA == TERMINAL_INPUT
    Error_State = USART_RecieveDataFuncName(&KPD_Press);
    // if user name length is valid
    if (Error_State == OK && CheckLength == 0)
    {
      // if user press enter
      if (KPD_Press == 0x0D || KPD_Press == 0x0F)
      {
      }
      // if user press back space
      else if (KPD_Press == 0x08)
      {
      }
      // if user enter valid data
      else
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendDataFuncName(KPD_Press);
#endif
        Check[CheckLength] = KPD_Press;
        CheckLength++;
      }
    }
    else if (Error_State == OK && CheckLength < PASSWORD_MAX_LENGTH)
    {
      if (KPD_Press == 0x0D || KPD_Press == 0x0F)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
        break;
      }
      else if (KPD_Press == 0x08)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        Clear_Char();
#endif
        CheckLength--;
      }
      else
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendDataFuncName(KPD_Press);
#endif
        Check[CheckLength] = KPD_Press;
        CheckLength++;
      }
    }
    // if user name length is more than 20 do no thing exept enter and delete
    else if (Error_State == OK && CheckLength >= PASSWORD_MAX_LENGTH)
    {
      if (KPD_Press == 0x0D || KPD_Press == 0x0F)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SendCommandFuncName(CLCD_DISPLAYON_CURSOROFF);
#endif
        break;
      }
      else if (KPD_Press == 0x08)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        Clear_Char();
#endif
        CheckLength--;
      }

      else
      {
      }
    }
    else
    {
    }
#endif
  }

  /*___________________________________________________________________________________________________________________*/

  // Check if password is correct or not
  if (CheckLength == PassWord_Length)
  {
    for (u8 i = 0; i < PassWord_Length; i++)
    {
      if (Check[i] == '\0')
      {
        break;
      }
      if (Check[i] != EEPROM_FunReadName(EEPROM_PassWordStartLocation + i))
      {
        PassWord_Check_Flag = 0; // if the pasword is uncorrect make this flag to zero
      }
      else
      {
      }
    }
  }
  else if (CheckLength != PassWord_Length)
  {
    PassWord_Check_Flag = 0; // if CheckLength != PassWord_Length make it false with out checking
  }
  else
  {
  }
}

//======================================================================================================================================//

/**
 * @brief Manages the complete login process
 * @details
 * - Coordinates username and password validation
 * - Tracks and updates remaining login attempts
 * - Provides feedback on failed attempts
 * - Triggers timeout when attempts exhausted
 * - Resets attempt counter on successful login
 */
void Sign_In(void)
{
  while (1)
  {
    /* get username and password from user */
    UserName_Check();
    PassWord_Check();
    // if any flag of them is zero that mean there is one of them is zero
    if (UserName_Check_Flag == 0 || PassWord_Check_Flag == 0)
    {
#if OUTPUT_SCREEN == CLCD_OUTPUT
      CLCD_ClearScreenFuncName();
      CLCD_SendStringFuncName("Invalid Username");
      CLCD_SetPositionFuncName(2, 1);
      CLCD_SendStringFuncName("or Password");
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
      // if it false make tries--
      USART_SendStringFuncName("Invalid Username or Password");
      USART_SendDataFuncName(0X0D);
#endif
      Tries--;
      EEPROM_FunWriteName(EEPROM_NoTries_Location, Tries);

      // if there tries i can use
      if (Tries > 0)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SetPositionFuncName(3, 1);
        CLCD_SendStringFuncName("Tries Left : ");
        CLCD_SendDataFuncName(Tries + 48);
        _delay_ms(700);
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
        USART_SendStringFuncName("Tries Left : ");
        USART_SendDataFuncName(Tries + 48);
        USART_SendDataFuncName(0X0D);
#endif
      }
      // if there is no tries any more go to function time out to count few of seconds
      else if (Tries == 0)
      {
#if OUTPUT_SCREEN == CLCD_OUTPUT
        CLCD_SetPositionFuncName(3, 1);
        CLCD_SendStringFuncName("Tries Left : ");
        CLCD_SendDataFuncName(Tries + 48);
        _delay_ms(500);
        Error_TimeOut();
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
        USART_SendStringFuncName("Tries Left : ");
        USART_SendDataFuncName(Tries + 48);
        USART_SendDataFuncName(0X0D);
        Error_TimeOut();
#endif
      }
    }
    // if username and password are correct
    else
    {
#if OUTPUT_SCREEN == CLCD_OUTPUT
      CLCD_ClearScreenFuncName();
      CLCD_SendStringFuncName("Successfully");
      CLCD_SetPositionFuncName(2, 1);
      CLCD_SendStringFuncName("Sign in");
      _delay_ms(700);
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
      USART_SendStringFuncName("Successfully Sign in");
      EEPROM_FunWriteName(EEPROM_NoTries_Location, NOTPRESSED);
      Tries = Tries_Max;
      USART_SendDataFuncName(0X0D);
#endif
      break;
    }
  }
}

//======================================================================================================================================//

/**
 * @brief Handles timeout period after maximum failed attempts
 * @details
 * - Displays countdown timer (5 seconds)
 * - Updates display each second
 * - Resets attempt counter after timeout
 * - Clears timeout state in EEPROM
 */
void Error_TimeOut(void)
{
#if OUTPUT_SCREEN == CLCD_OUTPUT
  CLCD_ClearScreenFuncName();
  CLCD_SendStringFuncName("Time out :  ");
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
  USART_SendStringFuncName("Time out :");
#endif
  for (u8 i = 5; i > 0; i--)
  {
#if OUTPUT_SCREEN == CLCD_OUTPUT
    // show second left on lcd
    CLCD_SendCommandFuncName(CLCD_SHIFT_CURSOR_LEFT);
    CLCD_SendDataFuncName(i + 48);
    _delay_ms(1000);
#elif OUTPUT_SCREEN == TERMINAL_OUTPUT
    USART_SendDataFuncName(0X08);
    // show second left on lcd
    USART_SendDataFuncName(i + 48);
    _delay_ms(1000);
#endif
  }
#if OUTPUT_SCREEN == TERMINAL_OUTPUT
  USART_SendDataFuncName(0X0D);
#endif
  // to make tries address Not pressed that mean i dosent spend any tries and make tries == max tries again
  EEPROM_FunWriteName(EEPROM_NoTries_Location, NOTPRESSED);
  Tries = Tries_Max;
}

//======================================================================================================================================//
#if OUTPUT_SCREEN == CLCD_OUTPUT
/**
 * @brief Clears a character from LCD display
 * @details
 * - Moves cursor one position left
 * - Overwrites with space character
 * - Returns cursor to cleared position
 */
void Clear_Char()
{
  CLCD_SendCommandFuncName(CLCD_SHIFT_CURSOR_LEFT);
  CLCD_SendDataFuncName(' ');
  CLCD_SendCommandFuncName(CLCD_SHIFT_CURSOR_LEFT);
}
#endif
//======================================================================================================================================//
