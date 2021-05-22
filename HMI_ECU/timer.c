/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the Timer AVR driver
 *
 * Author: Hossam Ahmed
 *
 *******************************************************************************/
#include "timer.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the TIMER driver
 * 1. determine timer number.
 * 2. determine prescaler factor of timer clock.
 * 3. determine Config_Ptr->edge type in counter mode.
 * 4. determine timer mode.
 *
 */
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	/* switch on timers on AVR*/
	switch(Config_Ptr->timer)
	{
	case TIMER_0:
		/*switch on clock devision factor of Timer_0 Clock */
		switch(Config_Ptr->prescaler)
		{
		case F_CPU_256:
			CLEAR_BIT(TCCR0 , CS00);
			CLEAR_BIT(TCCR0 , CS01);
			SET_BIT(TCCR0 , CS02);
			break;
		case F_CPU_1024:
			SET_BIT(TCCR0 , CS00);
			CLEAR_BIT(TCCR0 , CS01);
			SET_BIT(TCCR0 , CS02);
			break;

		case F_CPU_64:
			SET_BIT(TCCR0 , CS00);
			SET_BIT(TCCR0 , CS01);
			CLEAR_BIT(TCCR0 ,CS02);
			break;

		case F_CPU_8:
			CLEAR_BIT(TCCR0 , CS00);
			SET_BIT(TCCR0 , CS01);
			CLEAR_BIT(TCCR0 , CS02);
			break;

		case F_CPU_1:
			SET_BIT(TCCR0 , CS00);
			CLEAR_BIT(TCCR0 , CS01);
			CLEAR_BIT(TCCR0 , CS02);
			break;
		case NO_CLOCK:
			CLEAR_BIT(TCCR0 , CS00);
			CLEAR_BIT(TCCR0 , CS01);
			CLEAR_BIT(TCCR0 , CS02);
			break;
		}
		/*switch on modes of timer*/
		switch(Config_Ptr->mode)
		{
		case Normal:
			SET_BIT(TCCR0,FOC0);
			CLEAR_BIT(TCCR0 ,WGM00);
			CLEAR_BIT(TCCR0 ,WGM01);
			/*set the initial value of counter*/
			TCNT0 = Config_Ptr->preload;
			//SET_BIT(TIMSK,TOIE0);//overflow interrupt enable
			//PORTB = TIMSK;
			break;


		case CTC:
			SET_BIT(TCCR0,FOC0);
			SET_BIT(TCCR0 ,WGM01);
			CLEAR_BIT(TCCR0 ,WGM00);
			/*set the initial value of counter*/
			TCNT0 = Config_Ptr->preload;
			/*set the value to generate interrupt signal on it*/
			OCR0 = Config_Ptr->OCR;
			break;


			/*mode to generate PWM signal*/
		case FastPWM:/*non inverted mode*/
			SET_BIT(TCCR0 ,WGM01);
			SET_BIT(TCCR0 ,WGM00);
			/*set the initial value of counter*/
			TCNT0 = Config_Ptr->preload;
			/*set the value to generate interrupt signal on it*/
			OCR0 = Config_Ptr->OCR;
			//non inverted mode.
			SET_BIT(TCCR0,COM01);
			CLEAR_BIT(TCCR0,COM00);
			break;


			/*counter mode which count specific event that happen*/
		case counter:
			SET_BIT(TCCR0,FOC0);
			SET_BIT(TCCR0 ,WGM01);
			CLEAR_BIT(TCCR0 ,WGM00);
			/*set the initial value of counter*/
			TCNT0 = Config_Ptr->preload;
			/*set the value to generate interrupt signal on it*/
			OCR0 = Config_Ptr->OCR;
			/*switch on which edge to increment counter on it*/
			switch(Config_Ptr->edge)
			{
			case FALLING:
				CLEAR_BIT(TCCR0 , CS00);
				SET_BIT(TCCR0 , CS01);
				SET_BIT(TCCR0 , CS02);
				break;
			case RISING:
				SET_BIT(TCCR0 , CS00);
				SET_BIT(TCCR0 , CS01);
				SET_BIT(TCCR0 , CS02);
				break;
			case NONE:
				break;
			}
			break;

		}
		break;


		/********************************************************************/
		/*Timer 1*/
		/********************************************************************/
		case TIMER_1:
			SET_BIT(PORTB,0);
			/*switch on clock devision factor of Timer_1 Clock */
			switch(Config_Ptr->prescaler)
			{
			case F_CPU_256:
				CLEAR_BIT(TCCR1B , CS10);
				CLEAR_BIT(TCCR1B , CS11);
				SET_BIT(TCCR1B , CS12);
				break;
			case F_CPU_1024:
				SET_BIT(PORTB,1);
				SET_BIT(TCCR1B , CS10);
				CLEAR_BIT(TCCR1B , CS11);
				SET_BIT(TCCR1B , CS12);
				break;

			case F_CPU_64:
				SET_BIT(TCCR1B , CS10);
				SET_BIT(TCCR1B , CS11);
				CLEAR_BIT(TCCR1B , CS12);
				break;

			case F_CPU_8:
				CLEAR_BIT(TCCR1B , CS10);
				SET_BIT(TCCR1B , CS11);
				CLEAR_BIT(TCCR1B , CS12);
				break;

			case F_CPU_1:
				SET_BIT(TCCR1B , CS10);
				CLEAR_BIT(TCCR1B , CS11);
				CLEAR_BIT(TCCR1B , CS12);
				break;
			case NO_CLOCK:
				CLEAR_BIT(TCCR1B , CS10);
				CLEAR_BIT(TCCR1B , CS11);
				CLEAR_BIT(TCCR1B , CS12);
				break;
			}
			switch(Config_Ptr->mode)
			{
			case Normal:
				SET_BIT(TCCR1A,FOC1A);
				SET_BIT(TCCR1A,FOC1B);
				CLEAR_BIT(TCCR1A ,WGM10);
				CLEAR_BIT(TCCR1A ,WGM11);
				CLEAR_BIT(TCCR1B ,WGM12);
				CLEAR_BIT(TCCR1B ,WGM13);
				/*set the initial value of the 16 bits register of counter*/
				TCNT1H = (Config_Ptr->preload>>8);
				TCNT1L = (Config_Ptr->preload);
				break;


			case CTC: //OCR not ICR
				SET_BIT(PORTB,2);
				SET_BIT(TCCR1A,FOC1A);
				SET_BIT(TCCR1A,FOC1B);
				SET_BIT(TCCR1B ,WGM12);
				/*set the initial value of the 16 bits register of counter*/
				TCNT1 = Config_Ptr->preload;
				/*set value to be the maximum value which generate interrupt on it*/
				OCR1A=Config_Ptr->OCR;
				break;




			case FastPWM://non inverted mode.

				// mode 14 ICR value is the top value.
				//OCR1A
				CLEAR_BIT(TCCR1A ,WGM10);
				SET_BIT(TCCR1A ,WGM11);
				SET_BIT(TCCR1B ,WGM12);
				SET_BIT(TCCR1B ,WGM13);
				ICR1L = Config_Ptr->ICR;
				//non inverted mode.
				SET_BIT(TCCR1A,COM1A1);
				CLEAR_BIT(TCCR1A,COM1A0);
				break;

			case counter:
				SET_BIT(TCCR1A,FOC1A);
				SET_BIT(TCCR1A,FOC1B);
				CLEAR_BIT(TCCR1A ,WGM10);
				CLEAR_BIT(TCCR1A ,WGM11);
				SET_BIT(TCCR1B ,WGM12);
				CLEAR_BIT(TCCR1B ,WGM13);
				/*set the initial value of the 16 bits register of counter*/
				TCNT1H = (Config_Ptr->preload>>8);
				TCNT1L = (Config_Ptr->preload);
				/*set value to be the maximum value which generate interrupt on it*/
				OCR1AH = (Config_Ptr->OCR>>8);
				OCR1AL = Config_Ptr->OCR; /* OCFA is the interrupt flag*/
				switch(Config_Ptr->edge)
				{
				case FALLING:
					CLEAR_BIT(TCCR1B , CS10);
					SET_BIT(TCCR1B , CS11);
					SET_BIT(TCCR1B , CS12);
					break;
				case RISING:
					SET_BIT(TCCR1B , CS10);
					SET_BIT(TCCR1B , CS11);
					SET_BIT(TCCR1B , CS12);
					break;
				case NONE:
					break;
				}
				break;

			}
			break;
	}

}

