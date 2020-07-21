#include <ReceiveCanAData.h>

void ReceiveCanAData::Operate(uint8_t index, CAN_RxHeaderTypeDef RxHeader, uint8_t data[], void(*transmit)(uint8_t *Buf, uint8_t Len))
{
	if (index >= CanChannelsCount)
		return;
	
	if (RxHeader.ExtId != CAN_ID_STD)
		return;
	
	Output result;
	result.channelId = index;
	result.commandId = ReceiveCanAData_COMMAND_ID;
	result.CanId = RxHeader.StdId;
	result.DLC = RxHeader.DLC;
	memcpy(result.data, data, RxHeader.DLC);
	
	if (*transmit != nullptr)
		(*transmit)((uint8_t*)&result, sizeof(Output) - 8 + RxHeader.DLC);
}