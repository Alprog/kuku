
#include "Routine.h"

#include "Instruction.h"
#include <iostream>

Routine::Routine(byte* ip)
	: ip { ip }
{
}

void Routine::run()
{
	performInstruction();
}

void Routine::performInstruction()
{
	while (true)
	{
		auto instruction = read<Instruction>();
		if (instruction == Instruction::int_set)
		{
			auto cellIndex = read<byte>();
			auto value = read<integer>();

			stack.Cells[cellIndex].integer = value;
		}
		else if (instruction == Instruction::int_add)
		{
			auto arg1 = read<byte>();
			auto arg2 = read<byte>();
			auto out = read<byte>();
			stack.Cells[out].integer = stack.Cells[arg1].integer + stack.Cells[arg2].integer;
		}
		else if (instruction == Instruction::print)
		{
			auto arg = read<byte>();
			std::cout << stack.Cells[arg].integer << std::endl;
		}
		else
		{
			break;
		}
	}
}

