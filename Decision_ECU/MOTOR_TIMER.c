/*
 * MOTOR_TIMER.c
 *
 *  Created on: 2/2/2020
 *      Author: Hossam Ahmed
 */
#include"timer.h"
#include"MOTOR_TIMER.h"
extern uint8 g_numberOfSeconds;/*number of seconds needed in timer*/
/*******************************************************************************
 *                      Functions Declaration                                  *
 *******************************************************************************/
/*Description:function to initialize timer and buzzer
 * 1. init timer with number of seconds
 * 2.init motor I/O pins
 * 3.make motor on*/
void Motor_Timer_init(uint16 secs,uint8 status )
{
	/*Timer initialize*/
	/*global interrupt enable */
	SET_BIT(SREG,7);
	/*assign seconds to determined ISR logic*/
	g_numberOfSeconds = secs;
	/*OCR value to make timer 1 generate compare interrupt on it*/
	uint16 OCR_Value = 977;
	/*Prescaler factor F_CPU/1024
	 * Timer : Timer 0
	 * trigger edge of counter mode : none
	 * timer mode CTC : to interrupt on compare match
	 * initial value =0
	 * ICR value =0
	 * OCR value :calculated above.
	 * */
	SET_BIT(TIMSK,OCIE1A);//set compare match interrupt Enable
	Timer_ConfigType config = {F_CPU_1024,TIMER_1,NONE,CTC,0,0,OCR_Value};
	Timer_init(&config);
	/*Motor initialize*/
	SET_BIT(Motor_PORT_DIR,Motor_Pin1);
	SET_BIT(Motor_PORT_DIR,Motor_Pin2);
	if(status == ON_CW)
	{
		Motor_CW();/*open door clock wise*/
	}
	else
	{
		Motor_Counter_CW();/*close door counter clock wise*/
	}
}
static void Motor_CW(void)
{
	/*on clockWise*/
	SET_BIT(Motor_PORT,Motor_Pin1);
	CLEAR_BIT(Motor_PORT,Motor_Pin2);
}
static void Motor_Counter_CW(void)
{
	/*on counter clockWise*/
	CLEAR_BIT(Motor_PORT,Motor_Pin1);
	SET_BIT(Motor_PORT,Motor_Pin2);
}
void Motor_Timer_Dinit(void)
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
	CLEAR_BIT(Motor_PORT,Motor_Pin1);
	CLEAR_BIT(Motor_PORT,Motor_Pin2);
}


