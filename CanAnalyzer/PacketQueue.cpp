#include <PacketQueue.h>


PacketQueue::PacketQueue(uint32_t bufferSize)
{
	start = 0;
	finish = 0;
	maxSize = bufferSize;
	storage = (USBPacketData*)calloc(bufferSize, sizeof(USBPacketData));
}

bool PacketQueue::Push(USBPacketData data)
{
	uint32_t newfinish = (finish + 1) % GetMaxSize();
	if (newfinish == start)
	{
		//overflow
		return false;
	}
		
	storage[newfinish] = data;
	finish = newfinish;
	return true;
}

USBPacketData PacketQueue::Pop(bool *isOk) 
{

	if (Size() == 0)
	{
		USBPacketData result = { 0 };
		if(isOk != nullptr)
			*isOk = false;
		return result;
	}
	
	if(isOk != nullptr)
		*isOk = true;
	
	start = (start + 1) % GetMaxSize();
	return storage[start];
}

uint32_t PacketQueue::Size() 
{
	if (finish > start)
	{
		return finish - start;
	}
	else if (finish < start)
	{			
		return (GetMaxSize() - start) + finish;
	}
	else
	{
		//equals
		return 0;
	}
}

void PacketQueue::Reset() 
{
	finish = 0;
	start = 0;
}

inline uint32_t PacketQueue::GetMaxSize()
{
	return maxSize;
}
