#pragma once

enum instruction_flags
{
	NONE = 0,

	ARG_A = 1 << 0,
	ARG_B = 1 << 1,
	ARG_Bx = 1 << 2,
	ARG_sBx = 1 << 3,
	ARG_C = 1 << 4,

	ARGS_NONE = NONE,
	ARGS_A = ARG_A,
	ARGS_AB = ARG_A | ARG_B,
	ARGS_ABx = ARG_A | ARG_Bx,
	ARGS_AsBx = ARG_A | ARG_sBx,
	ARGS_ABC = ARG_A | ARG_B | ARG_C,
	ARGS_Bx = ARG_Bx
};