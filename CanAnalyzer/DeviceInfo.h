#pragma once
#include <stm32f105xc.h>
#define COMMAND_ID 1

//package's id - 1
namespace DeviceInfo
{
	struct Output
	{
		uint8_t commandId;
		uint8_t uid[3];
		uint8_t channels : 3;
		uint8_t isSupportsCanB : 1;
	};
	
	bool Operate(uint8_t *Buf, uint8_t Len, void (*transmit)(uint8_t *Buf, uint8_t Len));
}