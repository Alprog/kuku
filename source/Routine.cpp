
#include "Routine.h"

#include "InstructionType.h"
#include <iostream>
#include "BaseInstruction.h"

Routine::Routine(byte* ip)
	: ip { ip }
{
	JumpTable::Init();
}

void Routine::run()
{
	performInstruction();
}

void Routine::performInstruction()
{
	while (true)
	{
		reinterpret_cast<BaseInstruction*>(ip)->execute(*this);
	}
}

