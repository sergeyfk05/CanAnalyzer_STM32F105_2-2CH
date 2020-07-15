#pragma once
#define CANSTATE_MIN_VALUE 0
#define CANSTATE_MAX_VALUE 2

namespace Channels
{
	enum CANState
	{
		Closed           = 0,
		OpenedNormal     = 1,
		OpenedListenOnly = 2
	};
}
