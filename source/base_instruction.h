
#pragma once

#include "instruction_type.h"
#include "types.h"
#include "routine.h"
#include "jump_table.h"

struct Base_instruction
{
	Instruction_type Type;

	inline void execute(Routine& routine)
	{
		Jump_table::execute_function[(byte)Type](routine);
	}

	inline size_t getSize()
	{
		return Jump_table::get_size_function[(byte)Type]();
	}

	inline size_t skip(Routine& routine)
	{
		routine.ip += getSize();
	}
};


