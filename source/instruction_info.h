
#pragma once

#include <vector>
#include "instruction_type.h"
#include "instruction_arg.h"

struct instruction_info
{
	instruction_type type;
	const char* name;
	int stack_change;
	std::vector<instruction_arg_meta_base*> arguments;

	std::string to_string(byte* ptr);
};