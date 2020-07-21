#pragma once
#include <stm32f105xc.h>
#include <stm32f1xx_hal.h>
#include <CANState.h>

namespace Indicators
{
	class IIndicator
	{
	public:
		virtual void PeriodicCallback() = 0;
		virtual void Transmitted() = 0;
		virtual void Received() = 0;
		virtual void SetCanState(Channels::CANState state) = 0;
		
	};
}
