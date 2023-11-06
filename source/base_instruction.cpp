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
