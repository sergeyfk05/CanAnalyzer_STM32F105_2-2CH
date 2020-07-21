#include <Led1Indicator.h>

namespace Indicators
{
	Led1Indicator::Led1Indicator()
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);
		
	}
	
	void Led1Indicator::SetLedState(LedColors color, GPIO_PinState state)
	{
		uint16_t pin;
		switch (color)
		{
		case LedColors::Red:
			pin = GPIO_PIN_4;
			break;
		case LedColors::Green:
			pin = GPIO_PIN_5;
			break;
		case LedColors::Blue:
			pin = GPIO_PIN_6;
			break;
		default:
			return;
			break;
		}
		
		state = state == GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET;
		
		HAL_GPIO_WritePin(GPIOA, pin, state);
	}
	
	void Led1Indicator::ToggleLedState(LedColors color)
	{
		uint16_t pin;
		switch (color)
		{
		case LedColors::Red:
			pin = GPIO_PIN_4;
			break;
		case LedColors::Green:
			pin = GPIO_PIN_5;
			break;
		case LedColors::Blue:
			pin = GPIO_PIN_6;
			break;
		default:
			return;
			break;
		}
		
		HAL_GPIO_TogglePin(GPIOA, pin);
	}
}