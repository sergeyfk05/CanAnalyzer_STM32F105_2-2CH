#pragma once
#include <stm32f105xc.h>
#include <ChannelInfo.h>
#include <DeviceInfo.h>

bool(*SelectCommand(uint8_t *Buf))(uint8_t*, uint8_t, void(*)(uint8_t*, uint8_t));
