
#pragma once

#include "base_instruction.h"
#include "routine.h"
#include <iostream>
#include "for_each.h"
#include "instruction_arg.h"

template <instruction_type Type>
struct instruction : base_instruction
{
	instruction() : base_instruction{ Type } {};

	char const* get_name() { return "unknown"; }

	void execute(routine& routine)
	{
		throw std::exception("not implemented");
	}
};

#define EMPTY (,)
#define FIRST(first, second) first
#define SECOND(first, second) second
#define INITIALIZATION(x) SECOND x { SECOND x }
#define ARGUMENT_META(x) new instruction_arg<FIRST x>
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
		std::string get_name() { return #NAME; } \
		std::vector<instruction_arg_base*> get_argsLine() { return { FOR_EACH( ARGUMENT_META, __VA_ARGS__) }; } \
		inline void execute(routine& routine)

#define Ins0(NAME) \
	using instruction_##NAME = instruction<instruction_type::NAME>; \
	template<> \
	struct instruction<instruction_type::NAME> : base_instruction \
	{ \
		instruction() : base_instruction{ instruction_type::NAME } {} \
		std::string get_name() { return #NAME; } \
		std::vector<instruction_arg_base*> get_argsLine() { return {}; } \
		inline void execute(routine& routine)

#pragma pack(1)

#define INT(name) (integer, name) 
#define BYTE(name) (byte, name) 

Ins(PUSH_INT, INT(value))
{
	cell cell;
	cell.integer = value;
	routine.stack.push(cell);
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

Ins0(PRINT)
{
	std::cout << routine.stack.head[-1].integer << std::endl;
	routine.stack.head--;
}};

Ins(SET_LOCAL, BYTE(index))
{
	std::cout << routine.stack.frame_start[index].integer << std::endl;
	routine.stack.head--;
}};

Ins0(END)
{
	routine.stop();
}};
