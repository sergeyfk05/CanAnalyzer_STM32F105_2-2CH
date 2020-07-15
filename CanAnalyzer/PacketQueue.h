#pragma once

#include <stm32f105xc.h>
#include <USBPacketData.h>

class PacketQueue {
private:
	uint32_t maxSize = 10;
	USBPacketData *storage;
	uint32_t start;   //последний прочтенный
	uint32_t finish;   //последний занесенный

public :
	PacketQueue(uint32_t bufferSize = 10);
	bool Push(USBPacketData data);
	USBPacketData Pop(bool *isOk = nullptr);
	uint32_t Size();
	void Reset();
	inline uint32_t GetMaxSize();
};
