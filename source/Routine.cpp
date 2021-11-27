
#include "Routine.h"

#include "Instruction.h"

void Routine::run()
{

}

void Routine::performInstruction()
{
	auto instruction = *reinterpret_cast<Instruction*>(ip++);
	if (instruction == Instruction::int_set)
	{
		auto value = *reinterpret_cast<integer*>(ip);
		ip += sizeof(integer);

		stack.Cells[0].integer = value;
	}
}