
#include"Buzzer_Timer.h"
#include"timer.h"
extern uint8 g_numberOfSeconds;/*number of seconds needed in timer*/
/*******************************************************************************
 *                      Functions Declaration                                  *
 *******************************************************************************/
/*Description:function to initialize timer and buzzer
 * 1. init timer with number of seconds
 * 2.init buzzer I/O pins
 * 3.make buzzer on*/
void Buzzer_Timer_init(uint16 secs)
{
	/*Timer initialize*/
	/*global interrupt enable */
	SET_BIT(SREG,7);
	/*assign seconds to determined ISR logic*/
	g_numberOfSeconds = secs;
	/*OCR value to make timer 1 generate compare interrupt on it*/
	uint16 OCR_Value = 977;
	/*Prescaler factor F_CPU/1024
	 * Timer : Timer 1
	 * trigger edge of counter mode : none
	 * timer mode CTC : to interrupt on compare match
	 * initial value =0
	 * ICR value =0
	 * OCR value :calculated above.
	 * */
	SET_BIT(TIMSK,OCIE1A);//set compare match interrupt Enable
	Timer_ConfigType config = {F_CPU_1024,TIMER_1,NONE,CTC,0,0,OCR_Value};
	Timer_init(&config);
	/*Buzzer initialize*/
	SET_BIT(Buzzer_PORT_DIR,Buzzer_Pin);
	SET_BIT(Buzzer_PORT,Buzzer_Pin);
}
void Buzzer_Timer_Dinit(void)
{
	/*Timer De_initialize*/
	/*Prescaler factor No_clock
	 * Timer : Timer 1
	 * trigger edge of counter mode : none
	 * timer mode CTC : to interrupt on compare match
	 * initial value =0
	 * ICR value =0
	 * OCR value :0.
	 * */
	CLEAR_BIT(TIMSK,OCIE1A);//clear compare match interrupt Enable
	Timer_ConfigType config = {NO_CLOCK,TIMER_1,NONE,CTC,0,0,0};
	Timer_init(&config);
	/*Buzzer De_initialize*/
	CLEAR_BIT(Buzzer_PORT,Buzzer_Pin);
}
