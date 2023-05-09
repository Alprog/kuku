
#pragma once

#include "types.h"

enum class Instruction_type : byte
{
	PUSH_INT,
	INT_ADD,
	INT_SUB,
	INT_MULTIPLY,
	INT_DIVIDE,
	INT_POWER,
	PRINT,
	SET_LOCAL,
	END
};