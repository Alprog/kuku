
#include "Instruction.h"
#include "Routine.h"
#include <iostream>

#define instruction(NAME, ...) { \
		Instruction instruction{ InstructionType::NAME, #NAME }; \
		struct \
		{ \
			static void body(Routine& routine, __VA_ARGS__) \

#define end } helper; instruction.reg(helper, decltype(helper)::body); }

Instruction InstructionSet::Instructions[256];
PerformFunctionPtr InstructionSet::PerformFunctions[256];

void InstructionSet::Init()
{
	instruction(INT_SET, integer value, byte cellIndex)
	{
		routine.stack.Cells[cellIndex].integer = value;
	}
	end

	instruction(INT_ADD, byte arg1, byte arg2, byte out)
	{
		routine.stack.Cells[out].integer = routine.stack.Cells[arg1].integer + routine.stack.Cells[arg2].integer;
	}
	end

	instruction(PRINT, byte arg)
	{
		std::cout << routine.stack.Cells[arg].integer << std::endl;
	}
	end
}