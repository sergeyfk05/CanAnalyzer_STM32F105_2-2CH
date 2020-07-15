#include <CAN1Interface.h>

namespace Channels
{	
	
	CAN1Interface::CAN1Interface(uint8_t index)
	{
		this->index = index;
		state = CANState::Closed;
		
		GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		__HAL_RCC_CAN1_CLK_ENABLE();
		
		GPIO_InitStruct.Pin = GPIO_PIN_8;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		__HAL_AFIO_REMAP_CAN1_2();
		
		hcan.Instance = CAN1;
		hcan.Init.TimeTriggeredMode = DISABLE;
		hcan.Init.AutoBusOff = DISABLE;
		hcan.Init.AutoWakeUp = DISABLE;
		hcan.Init.AutoRetransmission = DISABLE;
		hcan.Init.ReceiveFifoLocked = DISABLE;
		hcan.Init.TransmitFifoPriority = DISABLE;
	}
	
	void CAN1Interface::Open(BitrateType bitrate, bool isListenOnly)
	{
		if (bitrate == BitrateType::undefined)
			return;
		
		CANState targetState = isListenOnly ? CANState::OpenedListenOnly :  CANState::OpenedNormal;
		if (this->bitrate == bitrate && this->state == targetState)
			return;
		
		hcan.Init.Mode = isListenOnly ? CAN_MODE_LOOPBACK : CAN_MODE_NORMAL;
		
		
		if (!GetTimings(bitrate, &hcan.Init.Prescaler, &hcan.Init.SyncJumpWidth, &hcan.Init.TimeSeg1, &hcan.Init.TimeSeg2))
			return;
		
		if (HAL_CAN_Init(&hcan) != HAL_OK)
		{
			return;
		}
		
		this->bitrate = bitrate;
		this->state = targetState;
		
		ChannelInfo::NotifyChanges(this->index, PushToUsbBuffer);
		//ChannelInfo::NotifyChanges(this->index, nullptr);
	}
	
	void CAN1Interface::Close()
	{
		HAL_CAN_DeInit(&hcan);
		this->state = CANState::Closed;
	}
	
	
}