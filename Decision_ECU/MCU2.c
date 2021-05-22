/*
 * MCU2.c
 *
 *  Created on: 31/2/2020
 *      Author: Hossam Ahmed
 */

#include"app_eeprom.h"
#include"app_uart.h"
#include"uart.h"
#include"Buzzer_Timer.h"
#include"MOTOR_TIMER.h"
/******************************************************************************
 * 						Global variables
 ******************************************************************************/
uint8 g_numberOfSeconds;/*number of seconds needed in timer*/

/******************************************************************************
 * 						Interrupt Service Routines
 ******************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	static uint8 Timer_Counter =0;
	Timer_Counter++;/*increment number of seconds*/
	if(g_numberOfSeconds == 15 && Timer_Counter ==15)
	{
		/*De_initialize Motor Timer to stop clock of timer*/
		Motor_Timer_Dinit();
		/*initialize timer to Rotate Motor for 15 seconds*/
		Motor_Timer_init(15,ON_counter_CW);/*close door*/
	}
	else if(g_numberOfSeconds == 15 && Timer_Counter ==30)
	{
		/*De_initialize Motor Timer to stop clock of timer*/
		Motor_Timer_Dinit();
		/*reset seconds counter*/
		Timer_Counter=0;
	}
	else if(g_numberOfSeconds == 60 && Timer_Counter ==60)
	{
		/*initialize timer to ON Buzzer for 60 seconds*/
		Buzzer_Timer_Dinit();
		/*reset seconds counter*/
		Timer_Counter =0;
	}

}
int main(void)
{
	uint8 checkFlag;
	uint8 received_status;
	uint8 received_Password[5];
	bool check_First_Time = TRUE; /*flag to indicate that program is in first iterate of infinite loop not to check for saved flag more than 1 time*/
	uint8 chances_Counter=0;/*3 chances for entering old password*/
	uint8 counter = 0;/*counter for password digit loop*/
	APP_EEPROM_init();
	APP_UART_init();
	/*first get flag that indicate that there is password in EEPROM or not*/
	checkFlag = APP_EEPROM_Get_CheckFlag();
	/*if saved state returned .. then it means that there is password and HMI ECU should display main screen*/
	while(1)
	{
		if(check_First_Time){
			if(checkFlag == SAVED)
			{
				/*send status to HMI ECU*/
					APP_UART_sendToHMI(SAVED);
			}
			else
			{
				/*send status to HMI ECU*/
				APP_UART_sendToHMI(NOT_SAVED);
			}
			check_First_Time = FALSE;
		}
		received_status = APP_UART_ReceiveFromHMI();
		switch(received_status)
		{
		/*save new password to EEPROM and change check flag to saved state*/
		case SAVED:
			/*receive password from HMI ECU*/
			APP_UART_ReceivePasswordFromHMI(received_Password);
			/*Save password in EEPROM*/
			APP_EEPROM_savePassword(received_Password);
			/*save states of saved password in EEPROM*/
			APP_EEPROM_Set_CheckFlag(SAVED);
			break;
		case CHECK:
			/*receive password and check if it matches*/
			if(APP_UART_ReceiveAndCheck())/*matches*/
			{
				APP_UART_sendToHMI(MATCH);
			}
			else
			{
				APP_UART_sendToHMI(UNMATCH);
			}
			break;

		case ALERT:
			/*on buzzer for 15 seconds */
			Buzzer_Timer_init(60);
			break;

		case DOOR_OPENED:
			/*initialize timer to Rotate Motor for 15 seconds*/
			Motor_Timer_init(15,ON_CW);
			break;

		}
	}
}

