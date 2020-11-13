#include <TransmitCanAData.h>


bool TransmitCanAData::Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len))
{
	if ((*Buf != TransmitCanAData_COMMAND_ID) || (Len < sizeof(Input) - 8))
		return false;
	
	Input* input = (Input*)Buf;
	
	if (input->channelId >= can_channels_count)
		return false;
	
	if (input->CanId > 0x7FF)
		return false;
	
	
	if (Len != sizeof(Input) - 8 + input->DLC)
		return false;
	
	CAN_TxHeaderTypeDef header;
	header.IDE = CAN_ID_STD;
	header.DLC = input->DLC;
	header.RTR = CAN_RTR_DATA;
	header.TransmitGlobalTime = DISABLE;
	header.StdId = input->CanId;
	
	can_channels[input->channelId]->Transmit(header, input->data);
}