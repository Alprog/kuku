
#pragma once

#include <vector>
#include "base_instruction.h"
#include "instruction_type.h"
#include "instruction_args.h"

struct instruction_info
{
	instruction_type type;
	const char* name;
	std::string comment;
	instruction_args args;

	bool has_arg(instruction_args arg) const;
	std::string to_string(base_instruction& instruction) const;
};