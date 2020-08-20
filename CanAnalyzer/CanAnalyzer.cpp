#include <CanAnalyzer.h>


int main(void)
{
	HAL_Init();
	SystemClock_Config();
	
	//HAL_Delay(5000);
	indicators[0] = new Led1Indicator();
	indicators[1] = new Led2Indicator();
	CanChannels[0] = new Channels::CAN2Interface(0, indicators[0]);
	CanChannels[1] = new Channels::CAN1Interface(1, indicators[1]);
	

	
	USBD_Init(&USBD_Device, &VCP_Desc, 0);

	USBD_RegisterClass(&USBD_Device, &USBD_CDC);
	USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_CanAnalyzer_fops);
	USBD_Start(&USBD_Device);
	
	while (true)
	{		
		USBTransmitInfinityLoop();
		USBRecieveInfinityLoop();	
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
	CanChannels[1]->ReceiveHandler();
}
extern "C" void CAN2_RX1_IRQHandler()
{
	CanChannels[0]->ReceiveHandler();
}
extern "C" void CAN2_RX0_IRQHandler()
{
	CanChannels[0]->ReceiveHandler();
}

void SysTick_Handler(void)
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
	USBPacketData data = TransmitUSBQueue->Pop(&isOk);
			
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
	USBPacketData data = RecieveUSBQueue->Pop(&isOk);
			
	if (!isOk)
		return;
		
	bool(*command)(uint8_t*, uint8_t, void(*)(uint8_t*, uint8_t));
	command = SelectCommand(data.Data);
	command(data.Data, data.Size, &PushToUsbBuffer);
}

