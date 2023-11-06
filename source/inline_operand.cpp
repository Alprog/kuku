#include "inline_operand.h"

byte inline_operand::to_RK_format()
{
	if (value >= 128)
	{
		throw std::exception("can't be represented in RK format");
	}

	if (is_constant)
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
		return { false, value };
	}
	else
	{
		return { true, (byte)(value - 128) };
	}
}