
#pragma once

#include "BaseInstruction.h"
#include "Routine.h"
#include <iostream>

template <InstructionType Type>
struct Instruction : BaseInstruction
{
	char const* getName() { return "unknown"; }

	void execute(Routine& routine)
	{
		throw std::exception("not implemented");
	}
};

#define Ins(NAME, ARGS) \
	template<> \
	struct Instruction<InstructionType::NAME> : BaseInstruction \
	{ \
		ARGS; \
		std::string getName() { return #NAME; } \
		std::string getArgsLine() { return #ARGS; } \
		inline void execute(Routine& routine)

#pragma pack(1)

Ins(INT_SET, byte cellIndex; integer value)
{
	routine.stack.Cells[cellIndex].integer = value;
}};

Ins(INT_ADD, byte arg1; byte arg2; byte out)
{
	routine.stack.Cells[out].integer = routine.stack.Cells[arg1].integer + routine.stack.Cells[arg2].integer;
}};

Ins(PRINT, byte arg)
{
	std::cout << routine.stack.Cells[arg].integer << std::endl;
}};