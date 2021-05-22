/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the Timer AVR driver
 *
 * Author: Hossam Ahmed
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum {
NO_CLOCK,
F_CPU_1,
F_CPU_8,
F_CPU_64,
F_CPU_256,
F_CPU_1024,
}Timer_PrescalerFactor;

typedef enum{
Normal,
CTC,
FastPWM,
counter,
}Timer_Mode;

typedef enum{
TIMER_0,TIMER_1
}Timer_Num;

typedef enum {
FALLING,
RISING,NONE,
}Timer_EdgeType;

typedef struct
{
	Timer_PrescalerFactor prescaler;
	Timer_Num timer;
	Timer_EdgeType edge;
	Timer_Mode mode;
	uint16 preload;
	uint16 ICR;
	uint16 OCR;
}Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the TIMER driver
 * 1. determine timer number.
 * 2. determine prescaler factor of timer clock.
 * 3. determine edge type in counter mode.
 * 4. determine timer mode.
 *
*/
void Timer_init(const Timer_ConfigType* Config_Ptr);


#endif /* TIMER_H_ */
