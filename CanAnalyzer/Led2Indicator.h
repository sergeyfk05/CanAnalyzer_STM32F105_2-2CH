#pragma once
#include <stm32f105xc.h>
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_gpio.h>
#include <LedIndicator.h>

namespace Indicators
{
	class Led2Indicator : public LedIndicator
	{
	public:
		Led2Indicator();
	private:
		void SetLedState(LedColors color, GPIO_PinState state);
		void ToggleLedState(LedColors color);
	};
}