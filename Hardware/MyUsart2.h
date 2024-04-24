#ifndef __MYUSART2_H
#define __MYUSART2_H
#include "stm32f10x.h"                  // Device header
extern uint16_t USART2_RxCounter;      
extern char USART2_RxBuff[1024]; 
extern uint16_t USART2_TxCounter;
extern char USART2_TxBuff[1024];

void u2_printf(char* fmt,...);
void Usart2_SendByte(uint16_t Data);
void MyUsart2_Init(void);
#endif

