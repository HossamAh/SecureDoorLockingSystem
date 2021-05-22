/*
 * Buzzer_Timer.h
 *
 *  Created on: 1/2/2020
 *      Author: Hossam Ahmed
 */

#include"std_types.h"
#ifndef BUZZER_TIMER_H_
#define BUZZER_TIMER_H_

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define Buzzer_PORT PORTD
#define Buzzer_PORT_DIR DDRD
#define Buzzer_Pin 7
/*******************************************************************************
 *                      Functions Declaration                                  *
 *******************************************************************************/
/*Description:function to initialize timer and buzzer
 * 1. init timer with number of seconds
 * 2.init buzzer I/O pins*/
void Buzzer_Timer_init(uint16 secs);
void Buzzer_Timer_Dinit(void);

#endif /* BUZZER_TIMER_H_ */
