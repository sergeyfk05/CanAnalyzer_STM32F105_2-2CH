#include <DeviceInfo.h>

bool DeviceInfo::Operate(uint8_t *Buf, uint8_t Len, void(*transmit)(uint8_t *Buf, uint8_t Len))
{
	if ((*Buf != COMMAND_ID) || (Len != 1))
		return false;
	
	Output result;
	result.commandId = COMMAND_ID;
	result.channels = 2;
	result.isSupportsCanB = 1;
	result.uid[0] = 1;
	result.uid[1] = 2;
	result.uid[2] = 3;
	
	if (*transmit != nullptr)
		(*transmit)((uint8_t*)&result, sizeof(Output));
	
	return true;
}