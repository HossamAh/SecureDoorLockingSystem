/*
 * HMI_ECU.c
 *
 *  Created on: 31/1/2020
 *  Author: Hossam Ahmed
 */
#include"keypad_UART.h"
#include"app_uart.h"
#include"lcd_Timer.h"
#include"uart.h"
#include"string.h"
static uint8 g_PW[5];
static uint8 g_currentMessage[16];
uint8 g_check = (uint8)0;
/*Description:Fucntion to deal with enter password and confirm it*/
void enter_PW_With_confirmation(void)
{
	uint8 counter = 0;
	uint8 key;
	bool check = FALSE;
	/*move cursor to line 2 and column 5*/
	LCD_goToRowColumn(1,4);
	/*looping for 5 times to get password from user*/
	for(;counter<5;counter++)
	{
		do{
			/*get digits of password */
			key = KeyPad_getPressedKey();

		}while(!(key>0 && key<=9));/*to ensure that the key inserted is digit not symbol or alphabet */
		_delay_ms(500);
		/*store password in array to check for it in confirmation step*/
		g_PW[counter] = key+48;

		/*print key on LCD Hashed*/
		LCD_displayCharacter('*');
	}
	/*confirmation step*/
	/**********************************************************************/
	/*clear screen from previous step data*/
	LCD_clearScreen();
	/*move cursor to line 1 and column 4*/
	LCD_goToRowColumn(0,3);
	/*loop until user enter same password again correctly*/
	while(!check)
	{

		/*reset counter to start check password again*/
		counter = 0;
		check = TRUE;
		/*clear screen Before each iteration*/
		LCD_clearScreen();
		/*print message on screen to enter the same password again*/
		LCD_displayString("Confirm Password:");
		/*move cursor to line 2 and column 5*/
		LCD_goToRowColumn(1,4);

		for(;counter<5;counter++)
		{
			do{
				/*get digits of password */
				key = KeyPad_getPressedKey();
			}while(!(key>0 && key<=9));/*to ensure that the key inserted is digit not symbol or alphabet */
			_delay_ms(500);
			/*check if key match the digit corresponding to in password array*/
			if(g_PW[counter] != (key+48))
			{
				check = FALSE;
			}
			/*print key on LCD Hashed*/
			LCD_displayCharacter('*');

		}
		/*displaying error msg if entered wrong password*/
		if(check == FALSE)
		{
			LCD_clearScreen();
			LCD_displayString("Wrong Password");
			_delay_ms(1000);
		}
	}

}

/*Description: Function to display main screen of APP:
 * 1. * change password
 * 2. # open door */
void display_Main_Screen(void)
{
	LCD_goToRowColumn(0,0);
	LCD_displayString("*:Change PW");
	LCD_goToRowColumn(1,0);
	LCD_displayString("#:Open Door");
	_delay_ms(1000);

}

/*Description:function to get old password from user and check from M2 whether it match old password or not
 * 1. get password from user and send each digit to M2 to check
 * 2. check on returned value from M2 for each digit if any of them is wrong or not
 * 3. iterate this process for 2 more times if the first iterate was wrong
 * 4. if all 3 chances are wrong .then return False */
bool get_And_Check_Old_PW(void)
{
	/*get old password from user using keypad and send to check*/
	uint8 counter = 0 ;
	uint8 key;
	uint8 status;
	/*send Check Command to M2 to check for old password*/
	APP_UART_SendKeyToDicisionECU('C');
	LCD_goToRowColumn(1,0);
	/*loop to get password digits from user*/
	for(;counter<5;counter++)
	{
		do{
			/*get digits of password */
			key = KeyPad_getPressedKey();
		}while(!(key>0 && key<=9));/*to ensure that the key inserted is digit not symbol or alphabet */
		_delay_ms(500);
		LCD_displayCharacter('*');
		/*send digit to M2 and receive ack*/
		APP_UART_SendKeyToDicisionECU(key+48);
	}
	status = APP_UART_GetKeyFromDicisionECU();
	/*password matching*/
	if(status == 'M')
	{
		return TRUE;
	}
	else if(status == 'E')
	{
		return FALSE;
	}
	else
	{
		return FALSE;
	}
}
/*function to check get password from user and check with the current stored password with three chances*/
bool check_password(uint8 key)
{
	bool status;
	uint8 chances_Counter = 0;/*counter for chances of open door or wrong password*/

	/*display message to enter old password*/
	for(;chances_Counter<3;chances_Counter++)
	{
		LCD_clearScreen();
		LCD_goToRowColumn(0,0);
		LCD_displayString(g_currentMessage);
		/*call function to get old password from user and check if it match stored password or not*/
		status = get_And_Check_Old_PW();
		if(status == TRUE)/*matching*/
		{
			if(key == '*')
			{
				g_check = 'N';/*to enter in new password mode*/
				return status;
			}
			else if(key == '#')
			{
				APP_UART_SendKeyToDicisionECU('O');//OPEN DOOR
				strcpy(g_currentMessage,"DOOR OPENED");
				LCD_Timer_init(15,g_currentMessage);
				return status;
			}

		}
		/*else display wrong msg and go to next chance*/
		LCD_clearScreen();
		LCD_goToRowColumn(0,0);
		LCD_displayString("ERROR:Wrong PW");
		LCD_goToRowColumn(1,0);
		LCD_intgerToString(2-chances_Counter);
		LCD_displayString(" times remain");
		_delay_ms(1000);
	}
	return status;
}

void Start_AlertLogic(void)
{
	APP_UART_SendKeyToDicisionECU('L');
	strcpy(g_currentMessage,"Alert");
	/*init timer to display alert message for 1 min*/
	LCD_Timer_init(60,g_currentMessage);
	g_check = 'E';
}
int main(void)
{
	bool CheckFirstIteration = FALSE;
	g_check = 'N';
	uint8 key;
	uint8 status;/*matching or not matching or door opened or door locked*/
	LCD_init();
	/*check whether its first time to open APP or not
	 * by using indicating flag in EEPROM . if check = 1 then there is password */
	KEYPAD_UART_init();
	while(1)
	{

		if((g_check == 'S' || g_check == 'N') && !CheckFirstIteration)
		{
			/*get password status from MC2 */
			g_check =APP_UART_GetKeyFromDicisionECU();
			CheckFirstIteration = TRUE;
		}

		/*there is password S(Saved) ..then open main screen*/
		if(g_check =='S' )
		{
			LCD_clearScreen();
			display_Main_Screen();
			/*get # or * from user*/
			do{
				key = KeyPad_getPressedKey();
			}while((key>=0 && key<=9));
			_delay_ms(500);
			if(key == '*')
			{
				strcpy(g_currentMessage,"enter old PW");
			}
			else if(key == '#')
			{
				strcpy(g_currentMessage,"enter PW");
			}
			status = check_password(key);
			if(status == FALSE)/*not matching in all chances*/
			{
				/*call function responsible for alerting logic*/
				Start_AlertLogic();
			}
			CheckFirstIteration = TRUE;
		}
		else if(g_check == 'N')/*new password is required N(Not Saved)*/
		{
			LCD_clearScreen();
			LCD_goToRowColumn(0,3);
			LCD_displayString("enter new PW");
			/*call this function to enter password and check confirmation*/
			enter_PW_With_confirmation();
			SET_BIT(PORTD,7);
			/*then after confirm password correctly start save it in EEPROM
			 *send digits to M2 to store it in EEPROM without checking
			 */
			KEYPAD_UART_Send_PW(g_PW);
			/*display correct password message*/
			LCD_clearScreen();
			LCD_displayString("Password saved");
			g_check = 'S';
			CheckFirstIteration = TRUE;
		}
	}
}
