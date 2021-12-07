
#pragma once

#include "InstructionType.h"
#include "types.h"
#include "string.h"
#include <vector>
#include "Routine.h"
#include "JumpTable.h"

struct BaseInstruction
{
	InstructionType Type;

	inline void execute(Routine& routine)
	{
		JumpTable::ExecuteFunction[(byte)Type](routine);
	}

	inline size_t getSize()
	{
		return JumpTable::GetSizeFunction[(byte)Type]();
	}

	inline size_t skip(Routine& routine)
	{
		routine.ip += getSize();
	}
};


