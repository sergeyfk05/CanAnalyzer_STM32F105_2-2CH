#pragma once
#include <stm32f105xc.h>
#include <stm32f1xx_hal.h>
#include <ICANChannel.h>
#include <BitrateType.h>
#include <CANState.h>
#include <GetChannelInfo.h>
#include <Helpers.h>

namespace Channels
{	
	class CAN1Interface : public ICANChannel
	{
	public:
		CAN1Interface(uint8_t index);
		
		void Open(BitrateType bitrate = BitrateType::kpbs500, bool isListenOnly = true);
		void Close();

		
	private:
		CAN_HandleTypeDef hcan;

		
	};
}

