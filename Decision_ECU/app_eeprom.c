/*
 * app_eeprom.c
 *
 *  Created on: 31/1/2020
 *      Author: Hossam Ahmed
 */
#include"app_eeprom.h"

/*******************************************************************************
 *                      Functions Definition                                   *
 *******************************************************************************/
/*Description:function to initialize EEPROM module*/
void APP_EEPROM_init(void)
{
	EEPROM_init();
}

/*Description :function to save new password in EEPROM*/
void APP_EEPROM_savePassword( uint8* a_PW)
{
	uint8 counter = 0;
	uint16 address = Password_Start_Address;

	/*Loop on password digits to store in EEPROM*/
	for(;counter<5;counter++)
	{
		/*store digit in EEPROM starting from first assigned address*/
		EEPROM_writeByte(address+counter,a_PW[counter]);
		_delay_ms(10);
	}
}

/*Description:function to check if password match or not*/
bool APP_EEPROM_checkPassword( uint8* a_PW)
{
	uint8 counter = 0;
	uint8 key;
	bool check = TRUE;
	uint16 address = Password_Start_Address;
	/*Loop on password digits to check if they match digits stored in EEPROM*/
	for(;counter<5;counter++)
	{
		/*get digit from EEPROM*/
		EEPROM_readByte(address+counter,&key);
		/*check if it matches or not and return false if any of them un-match*/
		if(key != a_PW[counter])
		{
			check = FALSE;
			break;
		}
	}
	return check;
}

/*Description: function to store check flag in EEPROM if there is password saved in eeprom or not*/
void APP_EEPROM_Set_CheckFlag( uint8 a_status)
{
	/*save status flag inside EEPPROM*/
	EEPROM_writeByte(CheckFlag_Address,a_status);
	_delay_ms(10);
	}

/*Description: function to get check flag from EEPROM */
uint8 APP_EEPROM_Get_CheckFlag(void)
{
	uint8 key;
	 EEPROM_readByte(CheckFlag_Address,&key);
	 return key;
	}
