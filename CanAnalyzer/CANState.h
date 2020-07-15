#pragma once

namespace Channels
{
	enum CANState
	{
		Closed           = 0,
		OpenedNormal     = 1,
		OpenedListenOnly = 2
	};
}
