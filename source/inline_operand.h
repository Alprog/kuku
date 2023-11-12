#pragma once

#include "types.h"
#include "instruction_mode.h"

struct inline_operand
{
	instruction_mode mode;
	byte value;

	byte to_RK_format();
	
	static inline_operand from_RK_format(byte value);
};