
#include "routine.h"
#include "base_instruction.h"

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

