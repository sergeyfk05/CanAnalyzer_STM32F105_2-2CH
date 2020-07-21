#include <LedIndicator.h>

namespace Indicators
{
	void LedIndicator::Transmitted()
	{
		SetLedState(Blue, GPIO_PIN_SET);
	}
	
	void LedIndicator::Received()
	{
		SetLedState(Green, GPIO_PIN_SET);
	}
	void LedIndicator::PeriodicCallback()
	{
		SetLedState(Green, GPIO_PIN_RESET);
		SetLedState(Blue, GPIO_PIN_RESET);
		
		if (state == Channels::CANState::OpenedListenOnly)
		{
			counter++;
			if (counter >= COUNTER_VALUE_TO_SWITCH)
			{
				counter = 0;
				ToggleLedState(Red);
			}
		}
	}
	
	void LedIndicator::SetCanState(Channels::CANState state)
	{
		this->state = state;
		counter = 0;
		
		switch (state)
		{
		case Channels::CANState::Closed:
			SetLedState(Red, GPIO_PIN_SET);
			break;
		case Channels::CANState::OpenedNormal:
			SetLedState(Red, GPIO_PIN_RESET);
			break;
		case Channels::CANState::OpenedListenOnly:
			SetLedState(Red, GPIO_PIN_SET);
			break;
		}
	}
}