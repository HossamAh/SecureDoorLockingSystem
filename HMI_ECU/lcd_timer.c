
#include"lcd_timer.h"
#include"timer.h"
extern uint8 g_check;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	static uint8 count=0;
	count++;/*increment number of seconds*/
	if(count == 15 && g_numberOfSeconds == 15)
	{
		LCD_clearScreen();
		/*De_initialize LCD Timer to stop clock of timer*/
		LCD_Timer_Dinit(15);
		/*initialize timer to display message for 15 seconds*/
		LCD_Timer_init(15,"DOOR LOCKED");
	}
	else if(count == 30 && g_numberOfSeconds == 15)
	{
		LCD_clearScreen();
		/*De_initialize LCD Timer to stop clock of timer*/
		LCD_Timer_Dinit(15);
		count =0;/*reset seconds counter */
		g_check = 'S';/*To return to main screen*/
	}
	else if(count == 60 && g_numberOfSeconds == 60)
	{
		LCD_clearScreen();
		/*De_initialize LCD Timer to stop clock of timer*/
		LCD_Timer_Dinit(60);
		g_check = 'S';/*To return to main screen*/
		count =0;/*reset seconds counter */
	}

}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*Description:function to initialize timer and LCD
 * 1. init timer with number of seconds
 * 2.display LCD message*/
void LCD_Timer_init(uint16 secs,uint8* Message)
{
	/*Timer initialize*/
	/*assign seconds to determined ISR logic*/
	g_numberOfSeconds = secs;
	/*set global interrupt enable bit*/
	SET_BIT(SREG,7);
	/*set compare match interrupt Enable*/
	SET_BIT(TIMSK,OCIE1A);
	/*OCR value to make timer 1 generate compare interrupt on it*/
	uint16 OCR_Value = 977;
	/*Prescaler factor F_CPU/1024
	 * trigger edge of counter mode : none
	 * timer mode CTC : to interrupt on compare match
	 * initial value =0
	 * ICR value =0
	 * OCR value :calculated above.
	 * */
	Timer_ConfigType config={F_CPU_1024,TIMER_1,NONE,CTC,0,0,OCR_Value};
	Timer_init(&config);
	/*LCD display messages*/
	LCD_clearScreen();
	LCD_goToRowColumn(0,2);
	LCD_displayString(Message);
	g_check='E';
}
void LCD_Timer_Dinit(uint8 secs)
{
	/*Timer initialize*/
	CLEAR_BIT(TIMSK,OCIE1A);//clear compare match interrupt Enable
	/*Prescaler factor F_CPU/1024
	 * trigger edge of counter mode : none
	 * timer mode CTC : to interrupt on compare match
	 * initial value =0
	 * ICR value =0
	 * OCR value :0
	 * */
	Timer_ConfigType config = {NO_CLOCK,TIMER_1,NONE,CTC,0,0,0};
	Timer_init(&config);
	/*LCD display messages*/
	LCD_clearScreen();
}
