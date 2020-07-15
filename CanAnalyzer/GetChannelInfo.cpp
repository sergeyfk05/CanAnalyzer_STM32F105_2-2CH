#include <GetChannelInfo.h>

bool GetChannelInfo::Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len))
{
	if ((*Buf != GetChannelInfo_COMMAND_ID) || (Len != sizeof(Input)))
		return false;
	
	Input* input = (Input*)Buf;
	
	if (input->channelId >= CanChannelsCount)
		return false;
	
	
	Output result;
	result.commandId = GetChannelInfo_COMMAND_ID;
	result.channelId = input->channelId;
	result.status = CanChannels[input->channelId]->GetState();
	result.bitrate = CanChannels[input->channelId]->GetBitrateType();
	result.bitrate = 8;
	
	if (*transmit != nullptr)
		(*transmit)((uint8_t*)&result, sizeof(Output));
	
	return true;
}

void GetChannelInfo::NotifyChanges(uint8_t index, void(*transmit)(uint8_t *Buf, uint8_t Len))
{
	if (index >= CanChannelsCount)
		return;
	
	Output result;
	result.commandId = GetChannelInfo_COMMAND_ID;
	result.channelId = index;
	result.status = CanChannels[index]->GetState();
	result.bitrate = CanChannels[index]->GetBitrateType();
	
	if (*transmit != nullptr)
		(*transmit)((uint8_t*)&result, sizeof(Output));
}