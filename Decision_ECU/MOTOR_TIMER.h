
#ifndef MOTOR_TIMER_H_
#define MOTOR_TIMER_H_

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define Motor_PORT PORTD
#define Motor_PORT_DIR DDRD
#define Motor_Pin1 3
#define Motor_Pin2 4
#define ON_CW 1
#define ON_counter_CW 0
/********************************************************************************
 * 						Private Functions
 *******************************************************************************/
static void Motor_Counter_CW(void);
static void Motor_CW(void);

/*******************************************************************************
 *                      Functions Declaration                                  *
 *******************************************************************************/
/*Description:function to initialize timer and motor
 * 1. init timer with number of seconds
 * 2.init motor I/O pins*/
void Motor_Timer_init(uint16 secs,uint8 status);
void Motor_Timer_Dinit(void);




#endif /* MOTOR_TIMER_H_ */
