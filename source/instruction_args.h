#pragma once

enum class instruction_args
{
	NONE = 0,

	A = 1 << 0,
	B = 1 << 1,
	Bx = 1 << 2,
	sBx = 1 << 3,
	C = 1 << 4,
};

inline constexpr instruction_args operator|(instruction_args lhs, instruction_args rhs) 
{
	return static_cast<instruction_args>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

inline constexpr instruction_args operator&(instruction_args lhs, instruction_args rhs)
{
	return static_cast<instruction_args>(static_cast<int>(lhs) & static_cast<int>(rhs));
}