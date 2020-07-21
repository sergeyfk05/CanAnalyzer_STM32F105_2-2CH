#pragma once
#include <stm32f105xc.h>
#include <ICANChannel.h>
#include <GetChannelInfo.h>
#include <Helpers.h>
#define TransmitCanBData_COMMAND_ID 5



extern Channels::ICANChannel* CanChannels[CHANNELS_COUNT];
extern uint8_t CanChannelsCount;

namespace TransmitCanBData
{
	struct Input
	{
		uint8_t commandId;
		uint8_t channelId : 3;
		uint8_t DLC : 4;
		uint32_t CanId;
		uint8_t data[8];
	};
	
	bool Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len));
	
}