#pragma once

#include "types.h"
#include "reflectable_enum.h"

#define CODES2(X) X, X##_K
#define CODES4(X) X, X##_KR, X##_RK, X##_KK

reflectable_enum(opcode, byte,
	CODES4(ADD),
	CODES4(SUB),
	CODES4(MULT),
	CODES4(DIVIDE),
	CODES4(POWER),
	CODES4(EQ),
	CODES4(NEQ),
	CODES4(L),
	CODES4(G),
	CODES4(LEQ),
	CODES4(GEQ),

	CODES2(ASSIGN),
	
	VALUE,
	PRINT,
	CREATE_OBJECT,
	SET_FIELD,
	VIRTUAL_CALL,
	JUMP,
	IFJUMP,
	INC,

	END
);
