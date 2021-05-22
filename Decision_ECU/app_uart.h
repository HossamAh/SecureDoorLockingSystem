/*
 * app_uart.h
 *
 *  Created on: 31/1/2020
 *      Author: Hossam Ahmed
 */

#ifndef APP_UART_H_
#define APP_UART_H_
#include"app_eeprom.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	SAVED='S',/*Saved status send to HMI ECU OR order to save Password from HMI ECU */
	NOT_SAVED='N',
	CHECK = 'C',
	UNMATCH = 'E',/*error ,not matches password in EEPROM*/
	MATCH = 'M',
	ALERT='L',/*for error logic*/
	DOOR_OPENED = 'O',
	DOOR_LOCKED = 'D',
}APP_UART_status;

/*******************************************************************************
 *                      Functions Declaration                                  *
 *******************************************************************************/
/*Description:Function to init uart module*/
void APP_UART_init(void);

/*Description:Function to send status to HMI ECU
 * 1.call UART function to send byte*/
void APP_UART_sendToHMI(const APP_UART_status a_status);
/*Description:Function to receive status from HMI ECU
 * 1.call UART function to receive byte*/
uint8 APP_UART_ReceiveFromHMI(void);

/*Description:function to receive password digits from HMI ECU and check whether they match or not*/
bool APP_UART_ReceiveAndCheck(void);
/*Description:Function to receive password from HMI ECU
 * 1.call UART function to receive string*/
void APP_UART_ReceivePasswordFromHMI(uint8* password);

#endif /* APP_UART_H_ */
