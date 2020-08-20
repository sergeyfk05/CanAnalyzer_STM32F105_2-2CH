#include <ICANChannel.h>


namespace Channels
{
	bool ICANChannel::GetTimings(BitrateType bitrate, uint32_t* prescaler, uint32_t* syncJumpWidth, uint32_t* timeSeg1, uint32_t* timeSeg2)
	{
		if (prescaler == nullptr || syncJumpWidth == nullptr || timeSeg1 == nullptr || timeSeg2 == nullptr)
			return false;
		
		*syncJumpWidth = CAN_SJW_1TQ;
		
		switch (bitrate)
		{
		case BitrateType::kpbs10:
			*prescaler = 200;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs20:
			*prescaler = 100;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs50:
			*prescaler = 40;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs83:
			*prescaler = 24;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs100:
			*prescaler = 20;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs125:
			*prescaler = 16;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs250:
			*prescaler = 8;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs500:
			*prescaler = 3;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs800:
			*prescaler = 5;
			*timeSeg1 = CAN_BS1_6TQ;
			*timeSeg2 = CAN_BS2_1TQ;
			break;
		case BitrateType::kpbs1000:
			*prescaler = 2;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		default:
			return false;
			break;
		}
		
		return true;
	}
	
	BitrateType ICANChannel::GetBitrateType()
	{
		return bitrate;
	}
	CANState ICANChannel::GetState()
	{
		return state;
	}
}