
#pragma once

#include <vector>
#include "instruction_arg.h"

struct instruction_info
{
	const char* name;
	std::vector<instruction_arg_meta_base*> arguments;
};