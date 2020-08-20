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
			*prescaler = 150;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs20:
			*prescaler = 75;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs50:
			*prescaler = 30;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs83:
			*prescaler = 18;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs100:
			*prescaler = 16;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs125:
			*prescaler = 12;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs250:
			*prescaler = 6;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs500:
			*prescaler = 3;
			*timeSeg1 = CAN_BS1_13TQ;
			*timeSeg2 = CAN_BS2_2TQ;
			break;
		case BitrateType::kpbs800:
			*prescaler = 3;
			*timeSeg1 = CAN_BS1_8TQ;
			*timeSeg2 = CAN_BS2_1TQ;
			break;
		case BitrateType::kpbs1000:
			*prescaler = 2;
			*timeSeg1 = CAN_BS1_10TQ;
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