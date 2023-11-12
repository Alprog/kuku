#include "base_instruction.h"

int base_instruction::get_argument_value(std::string name) const
{
	if (name == "A") return A;
	if (name == "B") return B;
	if (name == "C") return C;
	if (name == "Bx") return Bx;
	if (name == "sBx") return sBx;

	throw std::exception("trying to get not valid argument");
}

void base_instruction::set_B_cell(inline_operand operand)
{
	B = operand.value;
	MB = operand.mode;
}

void base_instruction::set_C_cell(inline_operand operand)
{
	C = operand.value;
	MC = operand.mode;
}