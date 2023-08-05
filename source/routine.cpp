
#include "routine.h"
#include "base_instruction.h"

routine::routine(byte* ip)
	: ip { ip }
{
	jump_table::init();
}

void routine::run()
{
	running = true;
	perform_instruction();
}

void routine::stop()
{
	running = false;
}

void routine::perform_instruction()
{
	while (running)
	{
		reinterpret_cast<base_instruction*>(ip)->execute(*this);
	}
}

