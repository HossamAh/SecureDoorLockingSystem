/*
 * app_uart.c
 *
 *  Created on: 31/2/2020
 *      Author: Hossam ahmed
 */

#include"app_uart.h"
#include"uart.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void APP_UART_init(void)
{
	UART_init_With_Interrupt();
}
 void App_UART_Deinit(void)
{
	UART_Deinit();
}
 uint8 APP_UART_GetKeyFromDicisionECU(void)
 {
	 uint8 key;
	 key = UART_recieveByte();
	 UART_sendByte('A');
	 _delay_ms(100);
	 return key;
 }
 void APP_UART_SendKeyToDicisionECU(const uint8 key)
 {
	 do
	 {
		 UART_sendByte(key);
		 _delay_ms(100);
	 }while(UART_recieveByte()!='A');
 }
