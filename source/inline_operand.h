#pragma once

#include "types.h"

struct inline_operand
{
	bool is_constant;
	byte value;

	byte to_RK_format();
	
	static inline_operand from_RK_format(byte value);
};