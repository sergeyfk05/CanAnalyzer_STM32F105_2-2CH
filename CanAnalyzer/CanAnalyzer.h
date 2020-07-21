#pragma once
#include <stm32f105xc.h>
#include <PacketQueue.h>
#include <CommandSelector.h>
#include <ICANChannel.h>
#include <CAN1Interface.h>
#include <Helpers.h>
#include <IIndicator.h>
#include <Led1Indicator.h>
#include <Led2Indicator.h>


using namespace Indicators;

#ifdef __cplusplus
extern "C"
{
#endif
#include <usbd_core.h>
#include <usbd_cdc.h>
#include "usbd_cdc_if.h"
#include <usbd_desc.h>

	USBD_HandleTypeDef USBD_Device;
	void SysTick_Handler(void);
	void OTG_FS_IRQHandler(void);
	void OTG_HS_IRQHandler(void);
	extern PCD_HandleTypeDef hpcd;
	void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
	void TIM2_IRQHandler();
	Indicators::IIndicator* indicators[2];

	
#ifdef __cplusplus
}
#endif

void USBTransmitInfinityLoop(void);
void USBRecieveInfinityLoop(void);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);



extern PacketQueue* RecieveUSBQueue;
extern PacketQueue* TransmitUSBQueue;
TIM_HandleTypeDef htim2;

Channels::ICANChannel* CanChannels[CHANNELS_COUNT];
uint8_t CanChannelsCount = CHANNELS_COUNT;
