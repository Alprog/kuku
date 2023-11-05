
#pragma once

#include <vector>
#include "base_instruction.h"
#include "opcode.h"
#include "instruction_args.h"

struct instruction_info
{
	opcode type;
	const char* name;
	std::string comment;
	instruction_args args;

	bool has_arg(instruction_args arg) const;
	std::string to_string(base_instruction& instruction) const;
};