

#ifndef LCD_TIMER_H_
#define LCD_TIMER_H_
#include"lcd.h"
/******************************************************************************
 * 						Global variables
 ******************************************************************************/
static uint8 g_numberOfSeconds;/*number of seconds needed in timer*/
/*******************************************************************************
 *                      Functions Declaration                                  *
 *******************************************************************************/
/*Description:function to initialize timer and LCD
 * 1. init timer with number of seconds
 * 2.display LCD message*/
void LCD_Timer_init(uint16 secs,uint8* Message);
void LCD_Timer_Dinit(uint8 secs);



#endif /* LCD_TIMER_H_ */
