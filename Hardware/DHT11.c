#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "DHT11.h"
#include "MyUsart1.h"
void DHT11_Init(void)
{	 
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
} 

u8 DHT11_RST(void)	   
{                 
	u8 cnt=0;
	DHT11_OUT(); 	
    GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
    Delay_ms(20);    	
    GPIO_SetBits(GPIOA,GPIO_Pin_5); 	 
	Delay_us(30);    	
	DHT11_IN();	 
    while (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==1&&cnt<100)
	{
		cnt++;
		Delay_us(1);
	};	 
	if(cnt>=100)
		return 1;
	else 
		cnt=0;
	//printf("cnt的值为%d\r\n",cnt);	
    while (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0&&cnt<100)
	{
		cnt++;
		Delay_us(1);
	};
	if(cnt>=100)
		return 1;    
	return 0;
}

u8 DHT11_Read_Bit(void) 			 
{
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==1);//检测到低电平
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0);////检测到高电平	
	Delay_us(35);		
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==1)
		return 1;
	else 
		return 0;		   
}

u8 DHT11_Read_Byte(void)    
{        
	u8 mask,dat;
	dat=0;
	for (mask=0x80;mask!=0;mask>>=1) 
	{
		if(DHT11_Read_Bit())
			dat |=mask;
		else
			dat &=~mask;	 	
	}						    
	return dat;
}
u8 DHT11_Read_Data(u8 *temperature,u8 *humidity)
{
	u8 i;
	u8 buf[5];
	if(DHT11_RST() == 0)
	{
		for(i = 0;i<5;i++)
		{
			buf[i] = DHT11_Read_Byte();
		
		}
		if ((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			 *humidity = buf[0];
			 *temperature = buf[2];
			return 0;		
		}
		else
			return 1;		
	}
	else
		return 1;

}

