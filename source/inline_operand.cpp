#include "inline_operand.h"

byte inline_operand::to_RK_format()
{
	if (value >= 128)
	{
		throw std::exception("can't be represented in RK format");
	}

	if (mode == instruction_mode::K)
	{
		return 128 + value;
	}
	else
	{
		return value;
	}
}

inline_operand inline_operand::from_RK_format(byte value)
{
	if (value < 128)
	{
		return { instruction_mode::R, value };
	}
	else
	{
		return { instruction_mode::K, (byte)(value - 128) };
	}
}