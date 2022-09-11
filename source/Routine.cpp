
#include "routine.h"
#include "base_instruction.h"

Routine::Routine(byte* ip)
	: ip { ip }
{
	Jump_table::init();
}

void Routine::run()
{
	running = true;
	perform_instruction();
}

void Routine::stop()
{
	running = false;
}

void Routine::perform_instruction()
{
	while (running)
	{
		reinterpret_cast<Base_instruction*>(ip)->execute(*this);
	}
}

