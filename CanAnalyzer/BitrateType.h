#pragma once
#define BITRATETYPE_MIN_VALUE 0
#define BITRATETYPE_MAX_VALUE 10

namespace Channels
{
	enum BitrateType
	{
		undefined = 0,
		kpbs10    = 1,
		kpbs20    = 2,
		kpbs50    = 3,
		kpbs83    = 4,
		kpbs100   = 5,
		kpbs125   = 6,
		kpbs250   = 7,
		kpbs500   = 8,
		kpbs800   = 9,
		kpbs1000  = 10
	};
}
