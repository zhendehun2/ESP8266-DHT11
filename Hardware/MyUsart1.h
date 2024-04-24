#ifndef __MYUSART1_H
#define __MYUSART1_H
#include "stm32f10x.h"                  // Device header
void MyUsart1_Init(void);
void Usart1_SendByte(uint16_t Data);
void u1_printf(char* fmt,...);
#endif
