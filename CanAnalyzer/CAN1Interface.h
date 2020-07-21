#pragma once
#include <stm32f105xc.h>
#include <stm32f1xx_hal.h>
#include <ICANChannel.h>
#include <BitrateType.h>
#include <CANState.h>
#include <GetChannelInfo.h>
#include <Helpers.h>
#include <ReceiveCanAData.h>
#include <ReceiveCanBData.h>
#include <IIndicator.h>

using namespace Indicators;

namespace Channels
{	
	class CAN1Interface : public ICANChannel
	{
	public:
		CAN1Interface(uint8_t index, IIndicator* indicator = nullptr);
		
		void Open(BitrateType bitrate = BitrateType::kpbs500, bool isListenOnly = true);
		void Close();
		void Transmit(CAN_TxHeaderTypeDef Header, uint8_t aData[]);
		void ReceiveHandler();
		
	private:
		CAN_HandleTypeDef hcan;
		CAN_FilterTypeDef canFilterConfig;
		uint32_t mailbox = CAN_TX_MAILBOX0;
		IIndicator* indicator;
		
	};
}

