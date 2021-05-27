

#include"keypad_UART.h"
#include"uart.h"
/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/* Description: Function to initialize Keypad and UART
 */
void KEYPAD_UART_init(void)
{
	/*initialize UART module*/
	UART_init();
}
/*Description :function to send password to M2 at first time in creating new password
 * 1. send PW to M2 */
void KEYPAD_UART_Send_PW(const uint8* a_PW)
{
	uint8 counter = 0;
	/* send status to save in EEPROM that password is determined*/
	do{
		_delay_ms(100);
		UART_sendByte('S');
	}while(UART_recieveByte() != 'A');

	for(;counter<5;counter++)
	{
		/*send PW to M2*/
		do{
			_delay_ms(100);
			UART_sendByte(a_PW[counter]);
		}while(UART_recieveByte() != 'A');
	}
}

/*Description :function to send  password to M2 and check if it is match or not
 * 1. send Password to M2
 * 2. check if the password  is matched with password in EEPROM */
bool KEYPAD_UART_Send_PW_And_Check(const uint8* a_PW)
{
	uint8 counter = 0;
	uint8 key;
	/* send status to check old password with password stored in EEPROM*/
	do{
		UART_sendByte('C');
		_delay_ms(100);
	}while(UART_recieveByte() != 'A');

	/*send key to check with digit in EEPROM*/
	for(;counter<5;counter++)
	{
		/*send PW to M2*/
		do{
			UART_sendByte(a_PW[counter]);
			_delay_ms(100);
			key =UART_recieveByte();
		}while( key != 'M' && key !='E');
		if(key == 'E')
		{
			return FALSE;
		}
	}
	return TRUE;
}
