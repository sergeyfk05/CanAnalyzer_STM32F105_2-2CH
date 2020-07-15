#include <CommandSelector.h>

bool(*SelectCommand(uint8_t *Buf))(uint8_t*, uint8_t, void(*)(uint8_t*, uint8_t))
{
	bool(*command)(uint8_t*, uint8_t, void(*)(uint8_t*, uint8_t));
	
	uint8_t commandId = *Buf;
	
	switch (commandId)
	{
	case 1: 
		command = DeviceInfo::Operate;
		break;
	case 2: 
		command = ChannelInfo::Operate;
		break;
	case 3: 
		command = nullptr;
		break;
	default: 
		command = nullptr;
		break;
		
	}
	
	
	
	
	
	return command;
}