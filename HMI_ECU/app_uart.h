#ifndef APP_UART_H_
#define APP_UART_H_
#include"std_types.h"

/*******************************************************************************
 *                      Functions Declaration                                  *
 *******************************************************************************/
void APP_UART_init(void);
void APP_UART_Get_Check_Flag(void);
void App_UART_Deinit(void);
uint8 APP_UART_GetKeyFromDicisionECU(void);
void APP_UART_SendKeyToDicisionECU(const uint8 key);

#endif /* APP_UART_H_ */
