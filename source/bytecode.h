
#pragma once

#include "types.h"
#include <stack>
#include "base_instruction.h"

#pragma pack(1)

class bytecode
{
public:
	std::vector<base_instruction> instructions;

	base_instruction* get_start_pointer();
	base_instruction* get_end_pointer();
};