#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyUsart1.h"
#include "MyUsart2.h"
#include "WIFI.h"
#include "stdlib.h"
#include "LED.h"
#include "DHT11.h"
uint16_t LEDState=0;
extern unsigned int rec_data[4];
int main(void)
{
	u8 temper;  	    
    u8 humi;
	u8 temp;
	LED_Init();
	OLED_Init();
	OLED_ShowString(1,1,"HELLO");
	DHT11_Init();
	MyUsart1_Init();
	MyUsart2_Init();
	ESP8266_Connect_to_TCP();
	StartSendData_ToServerByESP8266();
	uint16_t sendrand=0;
	u2_printf("abcd123\r\n");
	
	
	
	while(1)
	{
		Delay_ms(1000);
		temp = DHT11_Read_Data(&temper,&humi);
			if(temp ==0)
			{
				Senddata(temper);
			}
		LEDState=GetLEDstate();
		if(LEDState==2)
		{
			LED1_ON();
		}
		else if(LEDState==1)
		{
			LED1_OFF();
		}

           		
	}
}
