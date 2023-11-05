
#include "instruction_info.h"
#include "opcode.h"
#include <sstream>
#include <iomanip>

bool instruction_info::has_arg(instruction_args arg) const
{
	return (args & arg) != instruction_args::NONE;
}

std::string instruction_info::to_string(base_instruction& instruction) const
{
	std::stringstream ss;

	ss << std::left << std::setw(15) << name;
	
	auto print_value = [&](int value)
	{
		ss << std::left << std::setw(4) << std::to_string(value);
	};

	if (has_arg(instruction_args::A))
	{
		print_value( instruction.A );
	}
	if (has_arg(instruction_args::B))
	{
		print_value(instruction.B);
	}
	if (has_arg(instruction_args::Bx))
	{
		print_value(instruction.Bx);
	}
	if (has_arg(instruction_args::sBx))
	{
		print_value(instruction.sBx);
	}
	if (has_arg(instruction_args::C))
	{
		print_value(instruction.C);
	}


	return ss.str();
}
