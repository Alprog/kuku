#pragma once

#include "types.h"
#include "instruction_mode.h"

struct inline_operand
{
	instruction_mode mode;
	byte value;
};