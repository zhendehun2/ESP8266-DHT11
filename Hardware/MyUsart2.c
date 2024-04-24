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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��ʱ��A
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��ʱ��USART2
  //Ϊ��ʼ��������׼��
  GPIO_InitTypeDef GPIO_InitStructure;//����ṹ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//����PA2����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;//�������ģʽΪ�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//��������ٶ�Ϊ50MHZ
  //��ʼ������PIN2
  GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//����PA3����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//�������ģʽΪ��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//��������ٶ�Ϊ50MHZ
  //��ʼ������PIN3��
  GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��

  USART_InitTypeDef USART_InitStructure; //���崮�ڽṹ��
  USART_InitStructure.USART_BaudRate = 115200; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//����֡����
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //ֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No; //��ʹ��У��λ 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��ʹ��Ӳ��������
  USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //ģʽΪ����+����
  //��ʼ������2
  USART_Init(USART2, &USART_InitStructure); 

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
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
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//������λ�Ĵ����Ƿ�Ϊ
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



