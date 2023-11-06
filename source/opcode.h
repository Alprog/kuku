
#pragma once

#include "types.h"

enum class opcode : byte
{
	VALUE,
	CONSTANT,
	MOVE,
	ADD,
	SUB,
	MULTIPLY,
	DIVIDE,
	POWER,
	EQ,
	NEQ,
	L,
	G,
	LEQ,
	GEQ,
	PRINT,
	CREATE_OBJECT,
	SET_FIELD,
	VIRTUAL_CALL,
	JUMP,
	IFJUMP,

	END
};