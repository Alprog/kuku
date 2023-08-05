
#include "routine.h"
#include "base_instruction.h"

Routine::Routine(byte* ip)
	: ip { ip }
{
	jump_table::init();
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
		reinterpret_cast<base_instruction*>(ip)->execute(*this);
	}
}

