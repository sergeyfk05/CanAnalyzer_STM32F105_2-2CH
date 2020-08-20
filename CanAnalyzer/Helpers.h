#pragma once
#include <stm32f105xc.h>
#include  <PacketQueue.h>
#include <ICANChannel.h>
#define CHANNELS_COUNT 2


extern TIM_HandleTypeDef htim2;
extern PacketQueue* RecieveUSBQueue;
extern PacketQueue* TransmitUSBQueue;
//TIM_HandleTypeDef htim2;

void PushToUsbBuffer(uint8_t *Buf, uint8_t Len);

void SystemClock_Config(void);
void USBTransmitInfinityLoop(void);
void USBRecieveInfinityLoop(void);

