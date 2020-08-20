#pragma once
#include <stm32f105xc.h>
#include <stm32f1xx_hal.h>
#include <CANState.h>
#include <IIndicator.h>

#define COUNTER_VALUE_TO_SWITCH 250

namespace Indicators
{
	enum LedColors
	{
		Red,
		Green,
		Blue
	};
	
	class LedIndicator : public IIndicator
	{		
	public:
		void PeriodicCallback();
		void Transmitted();
		void Received();
		void SetCanState(Channels::CANState state);
	private:
		Channels::CANState state;
		uint16_t counter = 0;
		virtual void SetLedState(LedColors color, GPIO_PinState state) = 0;
		virtual void ToggleLedState(LedColors color) = 0;
	};
}
