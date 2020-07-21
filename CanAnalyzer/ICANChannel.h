#pragma once
#include <stm32f105xc.h>
#include <stm32f1xx_hal.h>
#include <BitrateType.h>
#include <CANState.h>

namespace Channels
{	
	class ICANChannel
	{
	public:
		virtual void Open(BitrateType bitrate = BitrateType::kpbs500, bool isListenOnly = true) = 0;
		virtual void Close() = 0;
		virtual void Transmit(CAN_TxHeaderTypeDef Header, uint8_t aData[]) = 0;
		virtual void ReceiveHandler() = 0;
		BitrateType GetBitrateType();
		CANState GetState();
		
	protected:
		bool GetTimings(BitrateType bitrate, uint32_t* prescaler, uint32_t* syncJumpWidth, uint32_t* timeSeg1, uint32_t* timeSeg2);
		uint8_t index;
		CANState state;
		BitrateType bitrate = BitrateType::undefined;
	};
}


