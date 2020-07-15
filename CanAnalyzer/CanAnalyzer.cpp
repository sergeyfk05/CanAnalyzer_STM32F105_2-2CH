#include <CanAnalyzer.h>


int main(void)
{
	HAL_Init();
	SystemClock_Config();
	
	CanChannels[0] = new Channels::CAN1Interface(0);
	
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
	if (((USBD_CDC_HandleTypeDef *)USBD_Device.pClassData)->TxState)
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