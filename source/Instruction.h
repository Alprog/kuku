
#pragma once

#include "InstructionType.h"
#include "types.h"
#include "string.h"
#include <vector>
#include "Routine.h"

using PerformFunctionPtr = void(*)(Routine&);

struct InstructionSet
{
	static void Init();

	static PerformFunctionPtr PerformFunctions[256];
};

struct Instruction
{
	InstructionType Type;

	inline void execute(Routine& routine)
	{
		InstructionSet::PerformFunctions[(byte)Type](routine);
	}
};



