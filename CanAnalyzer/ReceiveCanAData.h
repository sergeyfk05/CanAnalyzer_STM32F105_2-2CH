#pragma once
#include <stm32f105xc.h>
#include <ICANChannel.h>
#include <GetChannelInfo.h>
#include <Helpers.h>
#define ReceiveCanAData_COMMAND_ID 6



extern Channels::ICANChannel* can_channels[CHANNELS_COUNT];
extern uint8_t can_channels_count;

namespace ReceiveCanAData
{
	struct Output
	{
		uint8_t commandId;
		uint8_t channelId : 3;
		uint8_t DLC : 4;
		uint16_t CanId;
		uint32_t Time;
		uint8_t data[8];
	};
	
	void Operate(uint8_t index, CAN_RxHeaderTypeDef RxHeader, uint32_t time, uint8_t data[], void(*transmit)(uint8_t *Buf, uint8_t Len));
	
}