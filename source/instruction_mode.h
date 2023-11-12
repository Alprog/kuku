#pragma once

#include "types.h"

enum instruction_mode : uint8_t
{
	R = 0,
	K = 1,

	RR = 0,
	KR = 1,
	RK = 2,
	KK = 3
};