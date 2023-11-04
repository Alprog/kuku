
#pragma once

#include "base_instruction.h"
#include "routine.h"
#include <iostream>
#include "instruction_info.h"
#include "virtual_machine.h"
#include "instruction_args.h"
#include "preprocessor/for_each.h"
#include "protected_instruction.h"
#include "instruction_info.h"

#pragma warning( disable : 4003 )

#define MACRO_ARG_OPCODE (instruction_type, opcode)
#define MACRO_ARG_A (uint8_t, A)
#define MACRO_ARG_B (uint8_t, B)
#define MACRO_ARG_C (uint8_t, C)
#define MACRO_ARG_Bx (uint16_t, Bx)
#define MACRO_ARG_sBx (int16_t, sBx)

#define MACRO_ARGS_NONE
#define MACRO_ARGS_A    MACRO_ARG_A
#define MACRO_ARGS_AB   MACRO_ARG_A, MACRO_ARG_B
#define MACRO_ARGS_ABx  MACRO_ARG_A, MACRO_ARG_Bx
#define MACRO_ARGS_AsBx MACRO_ARG_A, MACRO_ARG_sBx
#define MACRO_ARGS_ABC  MACRO_ARG_A, MACRO_ARG_B, MACRO_ARG_C

#define FIRST(first, second) first
#define SECOND(first, second) second
#define BOTH(x) FIRST x SECOND x
#define USING(x) using base_instruction::SECOND x;
#define INITIALIZATION(x) this->SECOND x = SECOND x;
#define ARGUMENT(x) | CONCATENATE(instruction_args::, SECOND x)

template <instruction_type Type>
struct instruction : private protected_instruction
{
	inline void execute(routine& routine)
	{
		throw std::exception("not implemented");
	}

	static instruction_info create_info()
	{
		return { instruction_type::END, "unknown", "", instruction_args::NONE};
	}

	inline static instruction_info info = { instruction_type::END, "unknown", "", instruction_args::NONE };
};

#define Ins_X(NAME, COMMENT, ...) \
using instruction_##NAME = instruction<instruction_type::NAME>; \
template<> \
struct instruction<instruction_type::NAME> : public protected_instruction \
{ \
	using base_instruction::opcode; \
	FOR_EACH(USING, __VA_ARGS__) \
	instruction( FOR_EACH_WITH_COMMA(BOTH, __VA_ARGS__) ) \
	{ \
		opcode = instruction_type::NAME; \
		FOR_EACH(INITIALIZATION, __VA_ARGS__) \
	} \
	instruction(instruction<instruction_type::NAME>&&) = delete; \
	static instruction_info create_info() { return { instruction_type::NAME, #NAME, COMMENT, instruction_args::NONE FOR_EACH(ARGUMENT, __VA_ARGS__) }; } \
	inline void execute(routine& routine)

#define Ins(NAME, COMMENT, ARGUMENTS) Ins_X(NAME, COMMENT, EXPAND(CONCATENATE(MACRO_ARGS_, ARGUMENTS)))

//--------------------------------------------------------------------------------------------

Ins(SET_INT, "R(A) = INT(sBx)", AsBx)
{
	routine.stack.cells[A] = routine.stack.cells[sBx];
}};

Ins(MOVE, "R(A) = R(B)", AB)
{
	routine.stack.cells[A] = routine.stack.cells[B];
}};

Ins(INT_ADD, "R(A) = R(B) + R(C)", ABC)
{
	routine.stack.cells[A].integer = routine.stack.cells[B].integer + routine.stack.cells[C].integer;
}};

Ins(INT_SUB, "R(A) = R(B) - R(C)", ABC)
{
	routine.stack.cells[A].integer = routine.stack.cells[B].integer - routine.stack.cells[C].integer;
}};

Ins(INT_MULTIPLY, "R(A) = R(B) * R(C)", ABC)
{
	routine.stack.cells[A].integer = routine.stack.cells[B].integer * routine.stack.cells[C].integer;
}};

Ins(INT_DIVIDE, "R(A) = R(B) / R(C)", ABC)
{
	routine.stack.cells[A].integer = routine.stack.cells[B].integer / routine.stack.cells[C].integer;
}};

Ins(INT_POWER, "R(A) = R(B) ^ R(C)", ABC)
{
	routine.stack.head[A].integer = static_cast<integer>(std::pow(routine.stack.head[B].integer, routine.stack.head[C].integer));
}};

Ins(EQUAL, "R(A) = R(B) == R(C)", ABC)
{
	routine.stack.cells[A].boolean = routine.stack.cells[B].integer == routine.stack.cells[C].integer;
}};

Ins(NOT_EQUAL, "R(A) = R(B) != R(C)", ABC)
{
	routine.stack.cells[A].boolean = routine.stack.cells[B].integer != routine.stack.cells[C].integer;
}};

Ins(LESS, "R(A) = R(B) < R(C)", ABC)
{
	routine.stack.cells[A].boolean = routine.stack.cells[B].integer < routine.stack.cells[C].integer;
}};

Ins(GREATER, "R(A) = R(B) > R(C)", ABC)
{
	routine.stack.cells[A].boolean = routine.stack.cells[B].integer > routine.stack.cells[C].integer;
}};

Ins(LESS_OR_EQUAL, "R(A) = R(B) <= R(C)", ABC)
{
	routine.stack.cells[A].boolean = routine.stack.cells[B].integer <= routine.stack.cells[C].integer;
}};

Ins(GREATER_OR_EQUAL, "R(A) = R(B) >= R(C)", ABC)
{
	routine.stack.cells[A].boolean = routine.stack.cells[B].integer >= routine.stack.cells[C].integer;
}};

Ins(JUMP, "goto JMP(A)", A)
{
	routine.call_frame.ip += A;
}};

Ins(JUMP_ON_FALSE, "if !R(B) then goto JMP(A)", AB)
{
	if (!routine.stack.cells[B].boolean)
	{
		routine.call_frame.ip += A;
	}
}};

Ins(PRINT, "print R(A)", A)
{
	std::cout << routine.stack.cells[A].integer << std::endl;
}};

Ins(CREATE_OBJECT, "R(A) = new CLS(Bx)", ABx)
{
	routine.stack.cells[A].object_index = routine.vm.object_storage.create_object(Bx);
}};

Ins(SET_FIELD, "R(A).FLD(B) = R(C)", ABC)
{
	object_index object_index = routine.stack.cells[A].object_index;
	routine.vm.object_storage.get_object(object_index).data[B] = routine.stack.cells[C];
}};

Ins(VIRTUAL_CALL, "call FNC(B) with INT(A) args", AB)
{
	cell* frame_start = &routine.stack.cells[-A];
	object_header& self = routine.vm.object_storage.get_object(frame_start->object_index);
	rt::user_class& self_class = routine.vm.type_registry.classes[self.class_index];
	rt::function& function = self_class.vtable[B];
	routine.push_call_frame(function, frame_start);
}};

Ins(END, "end", NONE)
{
	routine.stop();
}};
