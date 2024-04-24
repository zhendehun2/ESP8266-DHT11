#include "stm32f10x.h"                  // Device header
#include "stdio.h"      
#include "stdarg.h"		
#include "string.h"

void MyUsart1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);//ʹ��ʱ��A��USART1

  //Ϊ��ʼ��������׼��
  GPIO_InitTypeDef GPIO_InitStructure;//����ṹ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//����PA9����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;//�������ģʽΪ�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//��������ٶ�Ϊ50MHZ
  //��ʼ������PIN9��
  GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//����PA10����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//�������ģʽΪ��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;//��������ٶ�Ϊ50MHZ
  //��ʼ������PIN10��
  GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��

  USART_InitTypeDef USART_InitStructure; //���崮�ڽṹ��
  USART_InitStructure.USART_BaudRate = 115200; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//����֡����
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //ֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No; //��ʹ��У��λ 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��ʹ��Ӳ��������
  USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //ģʽΪ����+����
  //��ʼ������1
  USART_Init(USART1, &USART_InitStructure); 

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

  //ʹ�ܴ���1
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
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//������λ�Ĵ����Ƿ�Ϊ
}






