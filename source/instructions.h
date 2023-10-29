
#pragma once

#include "base_instruction.h"
#include "routine.h"
#include <iostream>
#include "preprocessor/for_each.h"
#include "instruction_info.h"
#include "virtual_machine.h"

template <instruction_type Type>
struct instruction : base_instruction
{
	static const int stack_change = 0;

	instruction() : base_instruction{ Type } {};

	static instruction_info create_info() { return { Type, "unknown" }; }
	
	void execute(routine& routine)
	{
		throw std::exception("not implemented");
	}
};

#define FIRST(first, second) first
#define SECOND(first, second) second
#define BOTH(x) FIRST x SECOND x
#define DECLARARION(x) FIRST x SECOND x;
#define INITIALIZATION(x) , SECOND x { SECOND x }
#define ARGUMENT_META(x) instruction_arg_meta<FIRST x>::get_instance()

#define Ins_X(ARG_COUNT, NAME, STACK_CHANGE, ...) \
	using instruction_##NAME = instruction<instruction_type::NAME>; \
	template<> \
	struct instruction<instruction_type::NAME> : base_instruction \
	{ \
		static const int stack_change = STACK_CHANGE; \
		FOR_(ARG_COUNT, DECLARARION, __VA_ARGS__) \
		instruction( FOR_WITH_COMMA_(ARG_COUNT, BOTH, __VA_ARGS__) ) \
			: base_instruction{ instruction_type::NAME } \
			FOR_(ARG_COUNT, INITIALIZATION, __VA_ARGS__) \
		{ \
		} \
		static instruction_info create_info() { return { instruction_type::NAME, #NAME, STACK_CHANGE, { FOR_WITH_COMMA_(ARG_COUNT, ARGUMENT_META, __VA_ARGS__) } }; } \
		inline void execute(routine& routine)

#define Ins(...) EXPAND(Ins_X(VA_LENGTH_MINUS_2(__VA_ARGS__), __VA_ARGS__))

#pragma pack(1)

#define INT(name) (integer, name) 
#define BYTE(name) (byte, name) 
#define CLASS_INDEX(name) (class_index, name) 

Ins(PUSH_INT, +1, INT(value))
{
	routine.stack.push_integer(value);
}};

Ins(INT_ADD, -1)
{
	routine.stack.head[-2].integer += routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(INT_SUB, -1)
{
	routine.stack.head[-2].integer -= routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(INT_MULTIPLY, -1)
{
	routine.stack.head[-2].integer *= routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(INT_DIVIDE, -1)
{
	routine.stack.head[-2].integer /= routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(INT_POWER, -1)
{
	routine.stack.head[-2].integer = static_cast<integer>(std::pow(routine.stack.head[-2].integer, routine.stack.head[-1].integer));
	routine.stack.head--;
}};

Ins(EQUAL, -1)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer == routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(NOT_EQUAL, -1)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer != routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(LESS, -1)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer < routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(GREATER, -1)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer > routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(LESS_OR_EQUAL, -1)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer <= routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(GREATER_OR_EQUAL, -1)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer >= routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins(JUMP, 0, INT(jump_offset))
{
	routine.call_frame.ip += jump_offset;
}};

Ins(JUMP_ON_FALSE, 0, INT(jump_offset))
{
	if (routine.stack.head[-1].boolean)
	{
		routine.call_frame.ip += sizeof(instruction_JUMP_ON_FALSE);
	}
	else
	{
		routine.call_frame.ip += jump_offset;
	}
}};

Ins(PRINT, -1)
{
	std::cout << routine.stack.head[-1].integer << std::endl;
	routine.stack.head--;
}};

Ins(SET_LOCAL, -1, BYTE(index))
{
	routine.call_frame.start[index] = *--routine.stack.head;
}};

Ins(GET_LOCAL, +1, BYTE(index))
{
	routine.stack.push(routine.call_frame.start[index]);
}};

Ins(CREATE_OBJECT, +1, CLASS_INDEX(index))
{
	object_index object_index = routine.vm.object_storage.create_object(index);
	routine.stack.push_object_index(object_index);
}};

Ins(SET_FIELD, -1, BYTE(offset))
{
	object_index object_index = routine.stack.head[-2].object_index;
	routine.vm.object_storage.get_object(object_index).data[offset] = routine.stack.head[-1];
	routine.stack.head--;
}};

Ins(VIRTUAL_CALL, 0, BYTE(arguments_size), INT(function_index))
{
	cell* frame_start = &routine.stack.head[-arguments_size];
	object_header& self = routine.vm.object_storage.get_object(frame_start->object_index);
	rt::user_class& self_class = routine.vm.type_registry.classes[self.class_index];
	rt::function& function = self_class.vtable[function_index];
	routine.push_call_frame(function, frame_start);
}};

Ins(POP, -1, BYTE(count))
{
	routine.stack.head -= count;
}};

Ins(END, 0)
{
	routine.stop();
}};
