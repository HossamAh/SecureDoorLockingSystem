/*
 * app_uart.c
 *
 *  Created on: 31/1/2020
 *      Author: Hossam Ahmed
 */
#include"app_uart.h"
#include"uart.h"

/*******************************************************************************
 *                      Functions Definition                                  *
 *******************************************************************************/
/*Description:Function to init uart module*/
void APP_UART_init(void)
{
	UART_init();
}

/*Description:Function to send status to HMI ECU
 * 1.call UART function to send byte*/
void APP_UART_sendToHMI(const APP_UART_status a_status)
{
	do{
		/*send a_status to HMI*/
		_delay_ms(100);
		UART_sendByte(a_status);
	}while(UART_recieveByte() !='A' );
}
/*Description:Function to receive status or password  from HMI ECU
 * 1.call UART function to receive byte*/
uint8 APP_UART_ReceiveFromHMI(void)
{

	uint8 key =  UART_recieveByte();
	UART_sendByte('A');
	_delay_ms(100);
	return key;
}


/*Description:function to receive password digits from HMI ECU and check whether they match or not*/
bool APP_UART_ReceiveAndCheck(void)
{
	uint8 counter=0;
	uint8 key;
	uint8 check_Key;
	bool check = TRUE;
	for(;counter<5;counter++)
	{
		/*receive key from HMI ECU to check*/
		key = UART_recieveByte();
		/*send ack*/
		UART_sendByte('A');
		_delay_ms(100);
		/*check digit with digit in EEPROM*/
		EEPROM_readByte(Password_Start_Address+counter,&check_Key);
		if(key != check_Key){
			check =  FALSE;
		}
	}
	return check;
}

/*Description:Function to receive password from HMI ECU
 * 1.call UART function to receive string*/
void APP_UART_ReceivePasswordFromHMI(uint8 *password)
{
	uint8 counter=0;
	for(;counter<5;counter++)
	{
		password[counter] = UART_recieveByte();
		UART_sendByte('A');/*send ack*/
		_delay_ms(100);

	}
}
