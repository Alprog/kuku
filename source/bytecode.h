#pragma once

#include "types.h"
#include <vector>
#include "base_instruction.h"

class bytecode
{
public:
	std::vector<base_instruction> instructions;

	base_instruction* get_start_pointer();
	base_instruction* get_end_pointer();
};