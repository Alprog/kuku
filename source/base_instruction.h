
#pragma once

#include "instruction_type.h"
#include "types.h"
#include "routine.h"
#include "jump_table.h"

struct base_instruction
{
	instruction_type type;

	inline void execute(routine& routine)
	{
		jump_table::execute_function[(byte)type](routine);
	}

	inline size_t getSize()
	{
		return jump_table::get_size_function[(byte)type]();
	}

	inline size_t skip(routine& routine)
	{
		routine.call_frame.ip += getSize();
	}
};


