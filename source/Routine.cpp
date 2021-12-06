
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
		reinterpret_cast<Instruction*>(ip)->execute(*this);
	}
}

