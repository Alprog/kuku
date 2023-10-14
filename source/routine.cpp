
#include "routine.h"
#include "base_instruction.h"
#include "virtual_machine.h"

routine::routine(virtual_machine& vm, rt::function& function)
	: vm{ vm }
	, call_frame{ function, stack.cells }
{
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
		reinterpret_cast<base_instruction*>(call_frame.ip)->execute(*this);
	}
}

void routine::push_call_frame(rt::function& function)
{
	up_frames.push(call_frame);
	call_frame.function = function;
	call_frame.ip = function.bytecode.get_start_pointer();
	call_frame.start = stack.head;
}