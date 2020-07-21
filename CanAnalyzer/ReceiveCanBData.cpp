#include <ReceiveCanBData.h>

void ReceiveCanBData::Operate(uint8_t index, CAN_RxHeaderTypeDef RxHeader, uint8_t data[], void(*transmit)(uint8_t *Buf, uint8_t Len))
{
	if (index >= CanChannelsCount)
		return;
	
	if (RxHeader.ExtId != CAN_ID_EXT)
		return;
	
	Output result;
	result.channelId = index;
	result.commandId = ReceiveCanBData_COMMAND_ID;
	result.CanId = RxHeader.ExtId;
	result.DLC = RxHeader.DLC;
	memcpy(result.data, data, RxHeader.DLC);
	
	if (*transmit != nullptr)
		(*transmit)((uint8_t*)&result, sizeof(Output) - 8 + RxHeader.DLC);
}