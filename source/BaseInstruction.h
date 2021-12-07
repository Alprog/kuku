
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
};


