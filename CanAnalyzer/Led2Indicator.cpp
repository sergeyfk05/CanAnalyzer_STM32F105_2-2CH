#include <Led2Indicator.h>

namespace Indicators
{
	Led2Indicator::Led2Indicator()
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		
		GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
		
		GPIO_InitStruct.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		
	}
	
	void Led2Indicator::SetLedState(LedColors color, GPIO_PinState state)
	{
		uint16_t pin;
		GPIO_TypeDef* group;
		switch (color)
		{
		case LedColors::Red:
			group = GPIOA;
			pin = GPIO_PIN_7;
			break;
		case LedColors::Green:
			group = GPIOC;
			pin = GPIO_PIN_4;
			break;
		case LedColors::Blue:
			group = GPIOC;
			pin = GPIO_PIN_5;
			break;
		default:
			return;
			break;
		}
		
		state = state == GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET;
		
		HAL_GPIO_WritePin(group, pin, state);
	}
	
	void Led2Indicator::ToggleLedState(LedColors color)
	{
		uint16_t pin;
		GPIO_TypeDef* group;
		switch (color)
		{
		case LedColors::Red:
			group = GPIOA;
			pin = GPIO_PIN_7;
			break;
		case LedColors::Green:
			group = GPIOC;
			pin = GPIO_PIN_4;
			break;
		case LedColors::Blue:
			group = GPIOC;
			pin = GPIO_PIN_5;
			break;
		default:
			return;
			break;
		}
		
		HAL_GPIO_TogglePin(group, pin);
	}
}