#pragma once
#include <stm32f105xc.h>
#include <ICANChannel.h>
#include <GetChannelInfo.h>
#include <Helpers.h>
#define TransmitCanAData_COMMAND_ID 4



extern Channels::ICANChannel* can_channels[CHANNELS_COUNT];
extern uint8_t can_channels_count;

namespace TransmitCanAData
{
	struct Input
	{
		uint8_t commandId;
		uint8_t channelId : 3;
		uint8_t DLC : 4;
		uint16_t CanId;
		uint8_t data[8];
	};
	
	bool Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len));
	
}