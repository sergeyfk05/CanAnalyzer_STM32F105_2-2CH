#pragma once
#include <stm32f105xc.h>
#include <PacketQueue.h>
#include <CommandSelector.h>
#include <ICANChannel.h>
#include <CAN1Interface.h>
#include <CAN2Interface.h>
#include <Helpers.h>
#include <IIndicator.h>
#include <Led1Indicator.h>
#include <Led2Indicator.h>


//#define DEBUG_BUFFER


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
	void TIM2_IRQHandler();
	void CAN1_RX0_IRQHandler();
	void CAN2_RX1_IRQHandler();
	Indicators::IIndicator* indicators[CHANNELS_COUNT];
	
#ifdef DEBUG_BUFFER
	uint32_t RecieveUSBQueueCount;
	uint32_t TransmitUSBQueueCount;
#endif // DEBUG_BUFFER

	
#ifdef __cplusplus
}
#endif

void USBTransmitInfinityLoop(void);
void USBRecieveInfinityLoop(void);



extern PacketQueue* recieve_USB_queue;
extern PacketQueue* transmit_USB_queue;
TIM_HandleTypeDef htim2;

Channels::ICANChannel* can_channels[CHANNELS_COUNT];
uint8_t can_channels_count = CHANNELS_COUNT;
