#include <CAN2Interface.h>

namespace Channels
{	
	
	CAN2Interface::CAN2Interface(uint8_t index, IIndicator* indicator)
	{		
		this->indicator = indicator;
		this->index = index;
		state = CANState::Closed;
		
		if (indicator != nullptr)
			indicator->SetCanState(state);
		
		
		GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		__HAL_RCC_AFIO_CLK_ENABLE();
		__HAL_RCC_PWR_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_CAN2_CLK_ENABLE();
		
		GPIO_InitStruct.Pin = GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		__HAL_AFIO_REMAP_CAN2_ENABLE();
		
		hcan.Instance = CAN2;
		hcan.Init.TimeTriggeredMode = DISABLE;
		hcan.Init.AutoBusOff = DISABLE;
		hcan.Init.AutoWakeUp = DISABLE;
		hcan.Init.AutoRetransmission = DISABLE;
		hcan.Init.ReceiveFifoLocked = DISABLE;
		hcan.Init.TransmitFifoPriority = DISABLE;
		
		
		canFilterConfig.FilterBank = 1;
		canFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
		canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
		canFilterConfig.FilterIdHigh = 0x0000;
		canFilterConfig.FilterIdLow = 0x0000;
		canFilterConfig.FilterMaskIdHigh = 0x0000;
		canFilterConfig.FilterMaskIdLow = 0x0000;
		canFilterConfig.FilterFIFOAssignment = rxMailbox;
		canFilterConfig.FilterActivation = ENABLE;
		canFilterConfig.SlaveStartFilterBank = 15;
		
		HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
		HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
			

	}
	
	void CAN2Interface::Open(BitrateType bitrate, bool isListenOnly)
	{
		if (bitrate == BitrateType::undefined)
			return;
		
		CANState targetState = isListenOnly ? CANState::OpenedListenOnly :  CANState::OpenedNormal;
		if (this->bitrate == bitrate && this->state == targetState)
		{
			UpdateState();
			return;
		}
			
		
		hcan.Init.Mode = isListenOnly ? CAN_MODE_LOOPBACK : CAN_MODE_NORMAL;
		
		
		if (!GetTimings(bitrate, &hcan.Init.Prescaler, &hcan.Init.SyncJumpWidth, &hcan.Init.TimeSeg1, &hcan.Init.TimeSeg2))
			return;
		
		if ((HAL_CAN_Init(&hcan) != HAL_OK))
		{
			UpdateState();
			return;
		}
		if ((HAL_CAN_ConfigFilter(&hcan, &canFilterConfig) != HAL_OK))
		{
			UpdateState();
			return;
		}
		if ((HAL_CAN_Start(&hcan) != HAL_OK))
		{
			UpdateState();
			return;
		}
		
		this->bitrate = bitrate;
		this->state = targetState;
		
		HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
		HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO1_MSG_PENDING);
		//HAL_CAN_ActivateNotification(&hcan, CAN_IT_ERROR);
		
		UpdateState();

	}
	
	void CAN2Interface::UpdateState()
	{
		if (indicator != nullptr)
			indicator->SetCanState(state);
		GetChannelInfo::NotifyChanges(this->index, PushToUsbBuffer);
	}
	
	void CAN2Interface::Close()
	{
		if (HAL_CAN_Stop(&hcan) != HAL_OK)
		{
			GetChannelInfo::NotifyChanges(this->index, PushToUsbBuffer);
		}
		
		this->state = CANState::Closed;
		HAL_CAN_DeInit(&hcan);
		
		if (indicator != nullptr)
			indicator->SetCanState(state);

	}
	
	void CAN2Interface::Transmit(CAN_TxHeaderTypeDef Header, uint8_t aData[])
	{		
		HAL_CAN_AddTxMessage(&hcan, &Header, aData, &txMailbox);
		if (indicator != nullptr)
			indicator->Transmitted();
	}

	void CAN2Interface::ReceiveHandler()
	{
		uint8_t buf[8];
		CAN_RxHeaderTypeDef RxHeader;
		if (HAL_CAN_GetRxMessage(&hcan, rxMailbox, &RxHeader, buf) != HAL_OK)
			return;
		
		if (RxHeader.IDE == CAN_ID_STD)
		{
			ReceiveCanAData::Operate(this->index, RxHeader, buf, PushToUsbBuffer);
			
			if (indicator != nullptr)
				indicator->Received();
		}		
		else if (RxHeader.IDE == CAN_ID_EXT)
		{
			ReceiveCanBData::Operate(this->index, RxHeader, buf, PushToUsbBuffer);
			
			if (indicator != nullptr)
				indicator->Received();
		}
	}	
}