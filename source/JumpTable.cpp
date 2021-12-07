
#include "JumpTable.h"

#include "BaseInstruction.h"
#include "Routine.h"
#include <iostream>

#include "Instructions.h"

ExecuteFunctionPtr JumpTable::ExecuteFunction[256];

template <typename T>
inline void read_and_execute_instruction(Routine& routine)
{
	auto instruction = reinterpret_cast<T*>(routine.ip);
	instruction->execute(routine);
	routine.ip += sizeof(T);
}

template <typename T>
inline void get_size()
{
	return sizeof(T);
}

template <int I>
void registerInstruction()
{
	using InstructionT = Instruction<(InstructionType)I>;
	JumpTable::ExecuteFunction[I] = read_and_execute_instruction<InstructionT>;
}

template <int I>
void registerInstructionRecursive()
{
	registerInstruction<I>();
	registerInstructionRecursive<I - 1>();
}

template <>
void registerInstructionRecursive<0>()
{
	registerInstruction<0>();
}

void JumpTable::Init()
{
	registerInstructionRecursive<255>();
}
