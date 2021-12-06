
#include "Routine.h"

#include "InstructionType.h"
#include <iostream>
#include "Instruction.h"

Routine::Routine(byte* ip)
	: ip { ip }
{
	InstructionSet::Init();
}

void Routine::run()
{
	performInstruction();
}

void Routine::performInstruction()
{
	while (true)
	{
		auto instructionType = read<InstructionType>();
		InstructionSet::PerformFunctions[(byte)instructionType](*this);
	}
}

