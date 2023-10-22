
#pragma once

#include "base_instruction.h"
#include "routine.h"
#include <iostream>
#include "for_each.h"
#include "instruction_info.h"
#include "virtual_machine.h"

template <instruction_type Type>
struct instruction : base_instruction
{
	instruction() : base_instruction{ Type } {};

	static instruction_info create_info() { return { "unknown" }; }
	
	void execute(routine& routine)
	{
		throw std::exception("not implemented");
	}
};

#define EMPTY (,)
#define FIRST(first, second) first
#define SECOND(first, second) second
#define INITIALIZATION(x) SECOND x { SECOND x }
#define ARGUMENT_META(x) instruction_arg_meta<FIRST x>::get_instance()
#define BOTH(x) FIRST x SECOND x
#define SEMICOLON ;

#define Ins(NAME, ...) \
	using instruction_##NAME = instruction<instruction_type::NAME>; \
	template<> \
	struct instruction<instruction_type::NAME> : base_instruction \
	{ \
		FOR_EACH_SEPARATOR(BOTH, SEMICOLON, __VA_ARGS__); \
		instruction( FOR_EACH(BOTH, __VA_ARGS__) ) \
			: base_instruction{ instruction_type::NAME } \
			, FOR_EACH( INITIALIZATION, __VA_ARGS__) \
		{ \
		} \
		static instruction_info create_info() { return { #NAME, { FOR_EACH( ARGUMENT_META, __VA_ARGS__) } }; } \
		inline void execute(routine& routine)

#define Ins0(NAME) \
	using instruction_##NAME = instruction<instruction_type::NAME>; \
	template<> \
	struct instruction<instruction_type::NAME> : base_instruction \
	{ \
		instruction() : base_instruction{ instruction_type::NAME } {} \
		static instruction_info create_info() { return { #NAME }; } \
		inline void execute(routine& routine)

#pragma pack(1)

#define INT(name) (integer, name) 
#define BYTE(name) (byte, name) 
#define CLASS_INDEX(name) (class_index, name) 

Ins(PUSH_INT, INT(value))
{
	routine.stack.push_integer(value);
}};

Ins0(INT_ADD)
{
	routine.stack.head[-2].integer += routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins0(INT_SUB)
{
	routine.stack.head[-2].integer -= routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins0(INT_MULTIPLY)
{
	routine.stack.head[-2].integer *= routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins0(INT_DIVIDE)
{
	routine.stack.head[-2].integer /= routine.stack.head[-1].integer;
	routine.stack.head--;
}};

Ins0(INT_POWER)
{
	routine.stack.head[-2].integer = static_cast<integer>(std::pow(routine.stack.head[-2].integer, routine.stack.head[-1].integer));
	routine.stack.head--;
}};

Ins0(EQUAL)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer == routine.stack.head[-1].integer;
	routine.stack.head -= 2;
}};

Ins0(NOT_EQUAL)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer != routine.stack.head[-1].integer;
	routine.stack.head -= 2;
}};

Ins0(LESS)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer < routine.stack.head[-1].integer;
	routine.stack.head -= 2;
}};

Ins0(GREATER)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer > routine.stack.head[-1].integer;
	routine.stack.head -= 2;
}};

Ins0(LESS_OR_EQUAL)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer <= routine.stack.head[-1].integer;
	routine.stack.head -= 2;
}};

Ins0(GREATER_OR_EQUAL)
{
	routine.stack.head[-2].boolean = routine.stack.head[-2].integer >= routine.stack.head[-1].integer;
	routine.stack.head -= 2;
}};

Ins(JUMP, INT(jump_offset))
{
	routine.call_frame.ip += jump_offset;
}};

Ins(JUMP_ON_FALSE, INT(jump_offset))
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

Ins0(PRINT)
{
	std::cout << routine.stack.head[-1].integer << std::endl;
	routine.stack.head--;
}};

Ins(SET_LOCAL, BYTE(index))
{
	routine.call_frame.start[index] = *--routine.stack.head;
}};

Ins(GET_LOCAL, BYTE(index))
{
	routine.stack.push(routine.call_frame.start[index]);
}};

Ins(CREATE_OBJECT, CLASS_INDEX(index))
{
	object_index object_index = routine.vm.object_storage.create_object(index);
	routine.stack.push_object_index(object_index);
}};

Ins(SET_FIELD, BYTE(offset))
{
	object_index object_index = routine.stack.head[-2].object_index;
	routine.vm.object_storage.get_object(object_index).data[offset] = routine.stack.head[-1];
	routine.stack.head--;
}};

Ins(VIRTUAL_CALL, BYTE(arguments_size), INT(function_index))
{
	cell* frame_start = &routine.stack.head[-arguments_size];
	object_header& self = routine.vm.object_storage.get_object(frame_start->object_index);
	rt::user_class& self_class = routine.vm.type_registry.classes[self.class_index];
	rt::function& function = self_class.vtable[function_index];
	routine.push_call_frame(function, frame_start);
}};

Ins(POP, BYTE(count))
{
	routine.stack.head -= count;
}};

Ins0(END)
{
	routine.stop();
}};
