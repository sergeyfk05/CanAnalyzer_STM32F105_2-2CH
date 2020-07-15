#pragma once
#include <stm32f105xc.h>
#include  <PacketQueue.h>

extern PacketQueue* RecieveUSBQueue;
extern PacketQueue* TransmitUSBQueue;

void PushToUsbBuffer(uint8_t *Buf, uint8_t Len);

void SystemClock_Config(void);
void USBTransmitInfinityLoop(void);
void USBRecieveInfinityLoop(void);