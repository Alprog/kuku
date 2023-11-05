#pragma once

enum class instruction_args
{
	NONE = 0,

	A = 1 << 0,
	B = 1 << 1,
	C = 1 << 2,

	sA = 1 << 3,
	sB = 1 << 4,
	sC = 1 << 5,

	Bx = 1 << 6,
	sBx = 1 << 7,
};

inline constexpr instruction_args operator|(instruction_args lhs, instruction_args rhs) 
{
	return static_cast<instruction_args>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

inline constexpr instruction_args operator&(instruction_args lhs, instruction_args rhs)
{
	return static_cast<instruction_args>(static_cast<int>(lhs) & static_cast<int>(rhs));
}