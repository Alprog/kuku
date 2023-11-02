
#include "bytecode.h"

base_instruction* bytecode::get_start_pointer()
{
	return &instructions[0];
}

base_instruction* bytecode::get_end_pointer()
{
	return &instructions[instructions.size()];
}
