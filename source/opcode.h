#pragma once

#include "types.h"
#include "reflectable_enum.h"

#define CODES2(X) X, X##_K
#define CODES4(X) X, X##_RK, X##_KR, X##_KK

reflectable_enum(opcode, byte,
	CODES4(ADD),
	CODES4(SUB),
	CODES4(MULTIPLY),
	CODES4(DIVIDE),
	CODES4(POWER),
	CODES4(EQ),
	CODES4(NEQ),
	CODES4(L),
	CODES4(G),
	CODES4(LEQ),
	CODES4(GEQ),

	CODES2(MOVE),
	CODES2(IFJUMP),

	VALUE,
	CONSTANT,
	PRINT,
	CREATE_OBJECT,
	SET_FIELD,
	VIRTUAL_CALL,
	JUMP,

	END
);
