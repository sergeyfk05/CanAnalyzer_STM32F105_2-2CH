#pragma once
#include <stm32f105xc.h>
#include <ICANChannel.h>
#include <Helpers.h>
#define GetChannelInfo_COMMAND_ID 2



extern Channels::ICANChannel* can_channels[CHANNELS_COUNT];
extern uint8_t can_channels_count;

namespace GetChannelInfo
{
	struct Input
	{
		uint8_t commandId;
		uint8_t channelId : 3;
	};
	
	struct Output
	{
		uint8_t commandId;
		uint8_t channelId : 3;
		uint8_t status : 3;
		uint8_t bitrate : 4;
	};
	
	bool Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len));
	
	void NotifyChanges(uint8_t index, void(*transmit)(uint8_t *Buf, uint8_t Len));
}
