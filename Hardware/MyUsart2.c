#include "stm32f10x.h"                  // Device header
#include "stdio.h"      
#include "stdarg.h"		
#include "string.h"
uint16_t USART2_RxCounter = 0;      
char USART2_RxBuff[1024]; 
uint16_t USART2_TxCounter=0;
char USART2_TxBuff[1024];

void MyUsart2_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能时钟A
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能时钟USART2
  //为初始化函数做准备
  GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//设置PA2引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;//设置输出模式为复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//设置输出速度为50MHZ
  //初始化函数PIN2
  GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//设置PA3引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//设置输出模式为上拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//设置输出速度为50MHZ
  //初始化函数PIN3↓
  GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化

  USART_InitTypeDef USART_InitStructure; //定义串口结构体
  USART_InitStructure.USART_BaudRate = 115200; //波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//数字帧长度
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位
  USART_InitStructure.USART_Parity = USART_Parity_No; //不使用校验位 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不使用硬件流控制
  USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //模式为发送+接收
  //初始化串口2
  USART_Init(USART2, &USART_InitStructure); 

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能接收中断
  USART_Cmd(USART2,ENABLE);
  
  NVIC_InitTypeDef NVIC_Initstructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_Initstructure.NVIC_IRQChannel=USART2_IRQn;
  NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=1;
  NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;
  
  NVIC_Init(&NVIC_Initstructure);
  
}

void Usart2_SendByte(uint16_t Data)
{
	USART_SendData(USART2,Data);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
void u2_printf(char* fmt,...)
{
	unsigned int i=0,length=0;
	va_list ap;
	va_start(ap,fmt);
	vsprintf(USART2_TxBuff,fmt,ap);
	va_end(ap);
	
	length=strlen((const char*)USART2_TxBuff);
	while(i<length)
	{
		Usart2_SendByte(USART2_TxBuff[i]);
		i++;
	}
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//发送移位寄存器是否为
}
void USART2_IRQHandler(void) 
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {                               
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        USART2_RxBuff[USART2_RxCounter]=USART_ReceiveData(USART2);
   		USART2_RxCounter++;
	}
}



