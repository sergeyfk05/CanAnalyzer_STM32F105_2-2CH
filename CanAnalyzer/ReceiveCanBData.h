#pragma once
#include <stm32f105xc.h>
#include <ICANChannel.h>
#include <GetChannelInfo.h>
#include <Helpers.h>
#define ReceiveCanBData_COMMAND_ID 6



extern Channels::ICANChannel* CanChannels[CHANNELS_COUNT];
extern uint8_t CanChannelsCount;

namespace ReceiveCanBData
{
	struct Output
	{
		uint8_t commandId;
		uint8_t channelId : 3;
		uint8_t DLC : 4;
		uint32_t CanId;
		uint32_t Time;
		uint8_t data[8];
	};
	
	void Operate(uint8_t index, CAN_RxHeaderTypeDef RxHeader, uint8_t data[], void(*transmit)(uint8_t *Buf, uint8_t Len));
	
}