#ifndef __WIFI_H
#define __WIFI_H
#include "stm32f10x.h"                  // Device header
void WIFI_Config1(int time);
void WIFI_Config2(int time);
void WIFI_Config(int time,char*cmd,char*response);
void ESP8266_Connect_to_TCP(void);
void StartSendData_ToServerByESP8266(void);
uint16_t GetLEDstate(void);
void Senddata(uint16_t data);
#endif
