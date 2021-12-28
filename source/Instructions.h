
#pragma once

#include "base_instruction.h"
#include "routine.h"
#include <iostream>

template <Instruction_type Type>
struct Instruction : Base_instruction
{
	char const* get_name() { return "unknown"; }

	void execute(Routine& routine)
	{
		throw std::exception("not implemented");
	}
};

#define Ins(NAME, ARGS) \
	template<> \
	struct Instruction<Instruction_type::NAME> : Base_instruction \
	{ \
		ARGS; \
		std::string get_name() { return #NAME; } \
		std::string get_argsLine() { return #ARGS; } \
		inline void execute(Routine& routine)

#pragma pack(1)

Ins(INT_SET, byte cellIndex; integer value)
{
	routine.stack.cells[cellIndex].integer = value;
}};

Ins(INT_ADD, byte arg1; byte arg2; byte out)
{
	routine.stack.cells[out].integer = routine.stack.cells[arg1].integer + routine.stack.cells[arg2].integer;
}};

Ins(PRINT, byte arg)
{
	std::cout << routine.stack.cells[arg].integer << std::endl;
}};