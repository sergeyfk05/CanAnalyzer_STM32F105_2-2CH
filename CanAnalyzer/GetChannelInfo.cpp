#include <GetChannelInfo.h>

bool GetChannelInfo::Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len))
{
	if ((*Buf != GetChannelInfo_COMMAND_ID) || (Len != sizeof(Input)))
		return false;
	
	Input* input = (Input*)Buf;
	
	if (input->channelId >= can_channels_count)
		return false;
	
	
	Output result;
	result.commandId = GetChannelInfo_COMMAND_ID;
	result.channelId = input->channelId;
	result.status = can_channels[input->channelId]->GetState();
	result.bitrate = can_channels[input->channelId]->GetBitrateType();
	result.bitrate = 8;
	
	if (*transmit != nullptr)
		(*transmit)((uint8_t*)&result, sizeof(Output));
	
	return true;
}

void GetChannelInfo::NotifyChanges(uint8_t index, void(*transmit)(uint8_t *Buf, uint8_t Len))
{
	if (index >= can_channels_count)
		return;
	
	Output result;
	result.commandId = GetChannelInfo_COMMAND_ID;
	result.channelId = index;
	result.status = can_channels[index]->GetState();
	result.bitrate = can_channels[index]->GetBitrateType();
	
	if (*transmit != nullptr)
		(*transmit)((uint8_t*)&result, sizeof(Output));
}