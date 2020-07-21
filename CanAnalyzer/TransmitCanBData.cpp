#include <TransmitCanBData.h>


bool TransmitCanBData::Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len))
{
	if ((*Buf != TransmitCanBData_COMMAND_ID) || (Len < sizeof(Input) - 8))
		return false;
	
	Input* input = (Input*)Buf;
	
	if (input->channelId >= CanChannelsCount)
		return false;
	
	if (input->CanId > 0x1ffffff)
		return false;
	
	
	if (Len != sizeof(Input) - 8 + input->DLC)
		return false;
	
	CAN_TxHeaderTypeDef header;
	header.ExtId = CAN_ID_EXT;
	header.DLC = input->DLC;
	header.ExtId = input->CanId;
	
	CanChannels[input->channelId]->Transmit(header, input->data);
}