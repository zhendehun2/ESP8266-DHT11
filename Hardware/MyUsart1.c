#include "stm32f10x.h"                  // Device header
#include "stdio.h"      
#include "stdarg.h"		
#include "string.h"

void MyUsart1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);//使能时钟A和USART1

  //为初始化函数做准备
  GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//设置PA9引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;//设置输出模式为复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//设置输出速度为50MHZ
  //初始化函数PIN9↓
  GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//设置PA10引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//设置输出模式为上拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//设置输出速度为50MHZ
  //初始化函数PIN10↓
  GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化

  USART_InitTypeDef USART_InitStructure; //定义串口结构体
  USART_InitStructure.USART_BaudRate = 115200; //波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//数字帧长度
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位
  USART_InitStructure.USART_Parity = USART_Parity_No; //不使用校验位 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不使用硬件流控制
  USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //模式为发送+接收
  //初始化串口1
  USART_Init(USART1, &USART_InitStructure); 

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

  //使能串口1
  USART_Cmd(USART1, ENABLE);
}

void Usart1_SendByte(uint16_t Data)
{
	USART_SendData(USART1,Data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}
char USART1_TxBuff[256];

void u1_printf(char* fmt,...)
{
	unsigned int i=0,length=0;
	va_list ap;
	va_start(ap,fmt);
	vsprintf(USART1_TxBuff,fmt,ap);
	va_end(ap);
	
	length=strlen((const char*)USART1_TxBuff);
	while(i<length)
	{
		Usart1_SendByte(USART1_TxBuff[i]);
		i++;
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//发送移位寄存器是否为
}






