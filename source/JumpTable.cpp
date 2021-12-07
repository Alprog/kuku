
#include "JumpTable.h"
#include "Instructions.h"

ExecuteFunctionPtr JumpTable::ExecuteFunction[INSTRUCTION_COUNT];
GetSizeFunctionPtr JumpTable::GetSizeFunction[INSTRUCTION_COUNT];

template <typename T>
inline void readAndExecuteInstruction(Routine& routine)
{
	auto instruction = reinterpret_cast<T*>(routine.ip);
	instruction->execute(routine);
	routine.ip += sizeof(T);
}

template <typename T>
inline size_t getSize()
{
	return sizeof(T);
}

template <int I>
void registerInstruction()
{
	using InstructionT = Instruction<(InstructionType)I>;
	JumpTable::ExecuteFunction[I] = readAndExecuteInstruction<InstructionT>;
	JumpTable::GetSizeFunction[I] = getSize<InstructionT>;
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
