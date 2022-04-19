#include <CanAnalyzer.h>


int main(void)
{
	HAL_Init();
	SystemClock_Config();
	
	//HAL_Delay(5000);
	Led1Indicator led_indicator_0_ = Led1Indicator();
	Led2Indicator led_indicator_1_ = Led2Indicator();
	indicators[0] = &led_indicator_0_;
	indicators[1] = &led_indicator_1_;
	Channels::CAN1Interface channel_0_(0, indicators[0]);
	Channels::CAN2Interface channel_1_(1, indicators[1]);
	can_channels[0] = &channel_0_;
	can_channels[1] = &channel_1_;
	

	
	USBD_Init(&USBD_Device, &VCP_Desc, 0);

	USBD_RegisterClass(&USBD_Device, &USBD_CDC);
	USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_CanAnalyzer_fops);
	USBD_Start(&USBD_Device);
	
	while (true)
	{		
		USBTransmitInfinityLoop();
		USBRecieveInfinityLoop();
		
#ifdef DEBUG_BUFFER
		RecieveUSBQueueCount = RecieveUSBQueue->Size();
		TransmitUSBQueueCount = TransmitUSBQueue->Size();
#endif // DEBUG_BUFFER

	}

	
}

extern "C" void TIM2_IRQHandler()
{
	HAL_TIM_IRQHandler(&htim2);
	
	if (indicators[0] != nullptr)
		indicators[0]->PeriodicCallback();
	
	if (indicators[1] != nullptr)
		indicators[1]->PeriodicCallback();
}
extern "C" void CAN1_RX0_IRQHandler()
{
	can_channels[0]->ReceiveHandler();
}
extern "C" void CAN2_RX1_IRQHandler()
{
	can_channels[1]->ReceiveHandler();
}
extern "C" void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void OTG_FS_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&hpcd);
}

void USBTransmitInfinityLoop(void)
{
	bool isOk;
	USBPacketData data = transmit_USB_queue->Pop(&isOk);
			
	if (!isOk)
		return;
			
	//Wait for previous transfer
	if(((USBD_CDC_HandleTypeDef *)USBD_Device.pClassData)->TxState)
		return;
	
	USBD_CDC_SetTxBuffer(&USBD_Device, data.Data, data.Size);
	if (USBD_CDC_TransmitPacket(&USBD_Device) != USBD_OK)
	{
		//aaaaaaa
		return;
	}
}


void USBRecieveInfinityLoop(void)
{
	bool isOk;
	USBPacketData data = recieve_USB_queue->Pop(&isOk);
			
	if (!isOk)
		return;
		
	bool(*command)(uint8_t*, uint8_t, void(*)(uint8_t*, uint8_t));
	command = SelectCommand(data.Data);
	
	if (command != nullptr)
		command(data.Data, data.Size, &PushToUsbBuffer);
	else
	{
		uint8_t buf;
		PushToUsbBuffer(&buf, 0);
	}
}

