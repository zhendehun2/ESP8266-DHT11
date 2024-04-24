#ifndef __DHT11_H
#define __DHT11_H
#include "stm32f10x.h"                  
#define DHT11_IN()  {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=8<<5*4;}	
#define DHT11_OUT() {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=3<<5*4;}	
u8 DHT11_RST(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Data(u8 *temperature,u8 *humidity);
void DHT11_Init(void);
#endif
