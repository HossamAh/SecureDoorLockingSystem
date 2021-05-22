/*
 * keypad_UART.h
 *
 *  Created on: 31/1/2020
 *      Author: Hossam Ahmed
 */

#ifndef KEYPAD_UART_H_
#define KEYPAD_UART_H_
#include"keypad.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* Description: Function to initialize Keypad and UART
 */
void KEYPAD_UART_init(void);
/*Description :function to send password to M2 at first time in creating new password
 * 1. send PW to M2 */
void KEYPAD_UART_Send_PW(const uint8* a_PW);
/*Description :function to send  password to M2 and check if it is match or not
 * 1. send Password to M2
 * 2. check if the password  is matched with password in EEPROM */
bool KEYPAD_UART_Send_PW_And_Check(const uint8* a_PW);


#endif /* KEYPAD_UART_H_ */
