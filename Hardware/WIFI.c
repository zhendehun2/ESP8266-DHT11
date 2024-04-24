#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "string.h"
#include "MyUsart2.h"
#include "Delay.h"
#include "MyUsart1.h"
#define WiFi_RxCounter  USART2_RxCounter
#define WiFi_RX_BUF     USART2_RxBuff
#define WiFi_TxCounter  USART2_TxCounter
#define WiFi_TX_BUF     USART2_TxBuff
void WIFI_Config1(int time)
{
    memset(WiFi_RX_BUF,0,1024);
	WiFi_RxCounter=0;
	u2_printf("AT+RST\r\n");
	while(time--)
	{
		Delay_ms(100);
		if(strstr(WiFi_RX_BUF,"ready"))
		{
			break;
			u1_printf("%d",time);
		}
	}
		    
		    u1_printf("\r\n");
		if(time>0)
		{
			u1_printf("复位成功!\r\n"); 
		}
        else
            u1_printf("复位失败!\r\n");
}
void WIFI_Config2(int time)
{
	memset(WiFi_RX_BUF,0,1024);
	WiFi_RxCounter = 0;
	u2_printf("AT+CWMODE=1\r\n"); 
	while(time--)
	{
	  Delay_ms(100);
		if(strstr(WiFi_RX_BUF,"OK"))
		{
			break;
		}
		u1_printf ("%d ",time); 
	}
	u1_printf ("\r\n");
	if(time>0)
       u1_printf ("配置WIFI模式成功!\r\n"); 
    else
       u1_printf ("配置WIFI模式失败!\r\n");
}
uint16_t WIFI_Config(int time,char*cmd,char*response)
{
	uint16_t flag=0;
	memset(WiFi_RX_BUF,0,1024);
	WiFi_RxCounter = 0;
	u2_printf("%s\r\n",cmd);
	while(time--)
	{
		Delay_ms(100);
		if(strstr(WiFi_RX_BUF,response))
		{
			break;
		}
		u1_printf ("%d ",time);
	}
	u1_printf ("\r\n");
	if(time>0)
	{
		u1_printf("成功!\r\n");
		flag=1;
	}
	else{	
		u1_printf("失败\r\n");
	}
}
void ESP8266_Connect_to_TCP(void)
{
	if(WIFI_Config(100,"AT\r\n","OK"))
	{
		if(WIFI_Config(100,"AT+CWMODE=1\r\n","OK"))
		{
				if(WIFI_Config(100,"AT+CIPMUX=0\r\n","OK"))
				{
					if(WIFI_Config(100,"AT+CWJAP=\"mi\",\"304304lab\"\r\n","OK"))
					{
						if(WIFI_Config(100,"AT+CIPMODE=1\r\n","OK"))
						{
				         WIFI_Config(100,"AT+CIPSTART=\"TCP\",\"192.168.31.202\",9000","OK");
						}
					}
				}
			
		}
		
	}
//	WIFI_Config(100,"AT+RST\r\n","ready")
//	WIFI_Config(100,"AT+CIPSEND","OK");
}
void StartSendData_ToServerByESP8266(void)
{
	WIFI_Config(100,"AT+CIPSEND","OK");
}
uint16_t GetLEDstate(void)
{
	uint16_t State=0;
	if(strcmp(WiFi_RX_BUF,"1")==0)
	{
		State=2;
	}
	else if(strcmp(WiFi_RX_BUF,"0")==0)
	{
		
		State=1;
	}
	memset(WiFi_RX_BUF,0,1024);
	WiFi_RxCounter = 0;
	return State;
}
void Senddata(uint8_t data)
{
	memset(WiFi_TX_BUF,0,1024);
	sprintf(WiFi_TX_BUF,"%d",data);
	u2_printf(WiFi_TX_BUF);
}
