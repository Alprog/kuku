
#include "Instruction.h"
#include "Routine.h"
#include <iostream>

PerformFunctionPtr InstructionSet::PerformFunctions[256];


#pragma pack(1)

template <char const* name>
struct NamedInstruction : Instruction
{
	char const* getName()
	{
		return name;
	}
};

template <InstructionType Type>
struct Inst : Instruction
{
	char const* getName() { return "unknown"; }

	void execute(Routine& routine)
	{
		throw std::exception("not implemented");
	}
};

#define Instruction(NAME) \
	char NAME##_Name[] = #NAME; \
	template<> \
	struct Inst<InstructionType::NAME> : NamedInstruction<NAME##_Name>

Instruction(INT_SET)
{
	byte cellIndex; integer value;

	inline void execute(Routine& routine)
	{
		routine.stack.Cells[cellIndex].integer = value;
	}
};


Instruction(INT_ADD)
{
	byte arg1; byte arg2; byte out;

	inline void execute(Routine& routine)
	{
		routine.stack.Cells[out].integer = routine.stack.Cells[arg1].integer + routine.stack.Cells[arg2].integer;
	}
};

Instruction(PRINT)
{
	byte arg;

	inline void execute(Routine& routine)
	{
		std::cout << routine.stack.Cells[arg].integer << std::endl;
	}
};

template <typename T>
inline void read_and_execute_instruction(Routine& routine)
{
	auto instruction = reinterpret_cast<T*>(routine.ip);
	instruction->execute(routine);
	routine.ip += sizeof(T);
}

template <int I>
void registerInstruction()
{
	using InstructionT = Inst<(InstructionType)I>;
	InstructionSet::PerformFunctions[I] = read_and_execute_instruction<InstructionT>;
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

void InstructionSet::Init()
{
	registerInstructionRecursive<255>();
}
