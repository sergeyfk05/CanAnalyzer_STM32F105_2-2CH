#pragma once
#include <usbd_cdc.h>

struct USBPacketData
{
	uint8_t Data[CDC_DATA_FS_IN_PACKET_SIZE];
	uint32_t Size;
};
