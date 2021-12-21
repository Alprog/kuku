
#pragma once

#include "types.h"

enum class InstructionType : byte
{
	INT_SET,
	INT_ADD,
	INT_SUB,
	INT_MULTIPLY,
	INT_DIVIDE,
	PRINT,
	END
};