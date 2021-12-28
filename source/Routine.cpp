
#include "routine.h"
#include "base_instruction.h"

Routine::Routine(byte* ip)
	: ip { ip }
{
	Jump_table::init();
}

void Routine::run()
{
	perform_instruction();
}

void Routine::perform_instruction()
{
	while (true)
	{
		reinterpret_cast<Base_instruction*>(ip)->execute(*this);
	}
}

