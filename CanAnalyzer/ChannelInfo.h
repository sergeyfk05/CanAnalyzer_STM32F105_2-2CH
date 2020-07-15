#pragma once
#include <stm32f105xc.h>
//#include <CanAnalyzer.h>
#include <ICANChannel.h>
#define COMMAND_ID 2



extern Channels::ICANChannel* CanChannels[1];
extern uint8_t CanChannelsCount;

namespace ChannelInfo
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
		uint16_t bitrate : 10;
	};
	
	bool Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len));
	
	void NotifyChanges(uint8_t index, void(*transmit)(uint8_t *Buf, uint8_t Len));
}
