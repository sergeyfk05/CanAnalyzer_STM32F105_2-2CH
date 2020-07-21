#pragma once
#include <stm32f105xc.h>
#include <GetChannelInfo.h>
#include <DeviceInfo.h>
#include <SetChannelInfo.h>
#include <TransmitCanAData.h>
#include <TransmitCanBData.h>

bool(*SelectCommand(uint8_t *Buf))(uint8_t*, uint8_t, void(*)(uint8_t*, uint8_t));
