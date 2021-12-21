
#pragma once

#include "instruction_type.h"
#include "types.h"
#include "routine.h"
#include "jump_table.h"

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


