/*
 * app_eeprom.h
 *
 *  Created on: 31/1/2020
 *      Author: Hossam Ahmed
 */

#ifndef APP_EEPROM_H_
#define APP_EEPROM_H_
#include"std_types.h"
#include"external_eeprom.h"
#include"micro_config.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define CheckFlag_Address 0x0055
#define Password_Start_Address 0x00A0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Description:function to initialize EEPROM module*/
void APP_EEPROM_init(void);
/*Description :function to save new password in EEPROM*/
void APP_EEPROM_savePassword( uint8* a_PW);
/*Description:function to check if password match or not*/
bool APP_EEPROM_checkPassword( uint8* a_PW);
/*Description: function to store check flag in EEPROM if there is password saved in eeprom or not*/
void APP_EEPROM_Set_CheckFlag( uint8 a_status);

/*Description: function to get check flag from EEPROM */
uint8 APP_EEPROM_Get_CheckFlag(void);

#endif /* APP_EEPROM_H_ */
