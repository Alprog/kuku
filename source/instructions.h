
#pragma once

#include "base_instruction.h"
#include "routine.h"
#include <iostream>
#include "instruction_info.h"
#include "virtual_machine.h"
#include "instruction_flags.h"
#include "preprocessor/common.h"

#define ARG_A (uint8_t, A)
#define ARG_B (uint8_t, B)
#define ARG_C (uint8_t, C)
#define ARG_Bx (uint16_t, Bx)
#define ARG_sBx (int16_t, sBx)

#define ARGS_NONE
#define ARGS_A ARG_A
#define ARGS_AB ARG_A, ARG_B
#define ARGS_ABx ARG_A, ARG_Bx
#define ARGS_AsBx ARG_A, ARG_sBx
#define ARGS_ABC ARG_A, ARG_B, ARG_C



template<instruction_type Type>
instruction::flags instruction_flags = instruction::flags::ARGS_NONE;

template<instruction_type Type>
inline void execute(base_instruction& i, routine& routine)
{
	throw std::exception("not implemented");
}

#define Ins(OP_CODE, FLAGS) \
template<> instruction::flags instruction_flags<instruction_type::OP_CODE> = instruction::flags::ARGS_##FLAGS; \
template<> inline void execute<instruction_type::OP_CODE>(base_instruction& i, routine& routine) \

//--------------------------------------------------------------------------------------------

template<>
inline void execute<instruction_type::SET_CELL>(base_instruction& i, routine& routine)
{
	routine.stack.cells[i.A].integer = i.sBx;
};

Ins(INT_ADD_REG, ABC)
{
	routine.stack.cells[i.A].integer = routine.stack.cells[i.B].integer + routine.stack.cells[i.C].integer;
};

Ins(LESS_REG, ABC)
{
	routine.stack.cells[i.A].boolean = routine.stack.cells[i.B].integer < routine.stack.cells[i.C].integer;
};

Ins(SET_LOCAL_REG, AB)
{
	routine.stack.cells[i.A] = routine.stack.cells[i.B];
};

//--------------------------------------

Ins(INT_ADD, ABC, "R(A) = R(B) + R(C)")
{
	routine.stack.cells[i.A].integer = routine.stack.cells[i.B].integer + routine.stack.cells[i.C].integer;
};

Ins(INT_SUB, ABC, "R(A) = R(B) - R(C)")
{
	routine.stack.cells[i.A].integer = routine.stack.cells[i.B].integer - routine.stack.cells[i.C].integer;
};

Ins(INT_MULTIPLY, ABC, "R(A) = R(B) * R(C)")
{
	routine.stack.cells[i.A].integer = routine.stack.cells[i.B].integer * routine.stack.cells[i.C].integer;
};

Ins(INT_DIVIDE, ABC, "R(A) = R(B) / R(C)")
{
	routine.stack.cells[i.A].integer = routine.stack.cells[i.B].integer / routine.stack.cells[i.C].integer;
};

Ins(INT_POWER, ABC, "R(A) = R(B) ^ R(C)")
{
	routine.stack.head[i.A].integer = static_cast<integer>(std::pow(routine.stack.head[i.B].integer, routine.stack.head[i.C].integer));
};

Ins(EQUAL, ABC, "R(A) = R(B) == R(C)")
{
	routine.stack.cells[i.A].boolean = routine.stack.cells[i.B].integer == routine.stack.cells[i.C].integer;
};

Ins(NOT_EQUAL, ABC, "R(A) = R(B) != R(C)")
{
	routine.stack.cells[i.A].boolean = routine.stack.cells[i.B].integer != routine.stack.cells[i.C].integer;
};

Ins(LESS, ABC, "R(A) = R(B) < R(C)")
{
	routine.stack.cells[i.A].boolean = routine.stack.cells[i.B].integer < routine.stack.cells[i.C].integer;
};

Ins(GREATER, ABC, "R(A) = R(B) > R(C)")
{
	routine.stack.cells[i.A].boolean = routine.stack.cells[i.B].integer > routine.stack.cells[i.C].integer;
};

Ins(LESS_OR_EQUAL, ABC, "R(A) = R(B) <= R(C)")
{
	routine.stack.cells[i.A].boolean = routine.stack.cells[i.B].integer <= routine.stack.cells[i.C].integer;
};

Ins(GREATER_OR_EQUAL, ABC, "R(A) = R(B) >= R(C)")
{
	routine.stack.cells[i.A].boolean = routine.stack.cells[i.B].integer >= routine.stack.cells[i.C].integer;
};

Ins(JUMP, A, "goto JMP(A)")
{
	routine.call_frame.ip += i.A;
};

Ins(JUMP_ON_FALSE, AsBx, "if !R(A) then goto JMP(B)")
{
	if (!routine.stack.cells[i.A].boolean)
	{
		routine.call_frame.ip += i.sBx;
	}
};

Ins(PRINT, A, "print R(A)")
{
	std::cout << routine.stack.cells[i.A].integer << std::endl;
};

Ins(CREATE_OBJECT, ABx, "R(A) = new CLS(Bx)")
{
	routine.stack.cells[i.A].object_index = routine.vm.object_storage.create_object(i.Bx);
};

Ins(SET_FIELD, ABC, "R(A).FLD(B) = R(C)")
{
	object_index object_index = routine.stack.cells[i.A].object_index;
	routine.vm.object_storage.get_object(object_index).data[i.B] = routine.stack.cells[i.C];
};

Ins(VIRTUAL_CALL, AB, "call FNC(B) with INT(A) args")
{
	cell* frame_start = &routine.stack.cells[-i.A];
	object_header& self = routine.vm.object_storage.get_object(frame_start->object_index);
	rt::user_class& self_class = routine.vm.type_registry.classes[self.class_index];
	rt::function& function = self_class.vtable[i.B];
	routine.push_call_frame(function, frame_start);
};

Ins(END, NONE, "end")
{
	routine.stop();
};
