#include <SetChannelInfo.h>
using namespace Channels;

bool SetChannelInfo::Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len))
{ 
	//check arguments
	if((*Buf != SetChannelInfo_COMMAND_ID) || (Len != sizeof(Input)))
		return false;
	
	Input* input = (Input*)Buf;
	
	if (input->channelId >= CanChannelsCount)
		return false;
	
	if ((input->bitrate < BITRATETYPE_MIN_VALUE) || (input->bitrate > BITRATETYPE_MAX_VALUE) || (input->status < CANSTATE_MIN_VALUE) || (input->status > CANSTATE_MAX_VALUE))
	{
		GetChannelInfo::NotifyChanges(input->channelId, transmit);
		return false;
	}
	
	
	ICANChannel* ch = CanChannels[input->channelId];
	
	switch((CANState)input->status)
	{
	case Closed:
		ch->Close();
		break;
	case OpenedNormal:
		ch->Open((BitrateType)input->bitrate, false);
		break;
	case OpenedListenOnly:
		ch->Open((BitrateType)input->bitrate, true);
		break;
	default:
		break;
	}
	
	GetChannelInfo::NotifyChanges(input->channelId, transmit);
	
}