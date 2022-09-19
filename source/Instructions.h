
#pragma once

#include "base_instruction.h"
#include "routine.h"
#include <iostream>
#include "for_each.h"

template <Instruction_type Type>
struct Instruction : Base_instruction
{
	Instruction() : Base_instruction{ Type } {};

	char const* get_name() { return "unknown"; }

	void execute(Routine& routine)
	{
		throw std::exception("not implemented");
	}
};

#define EMPTY (,)
#define FIRST(first, second) first
#define SECOND(first, second) second
#define ASSIGN(x) this->SECOND x = SECOND x
#define BOTH(x) FIRST x SECOND x
#define SEMICOLON ;

#define Ins(NAME, ...) \
	using Instruction_##NAME = Instruction<Instruction_type::NAME>; \
	template<> \
	struct Instruction<Instruction_type::NAME> : Base_instruction \
	{ \
		FOR_EACH_SEPARATOR(BOTH, SEMICOLON, __VA_ARGS__); \
		Instruction( FOR_EACH(BOTH, __VA_ARGS__) ) \
			: Base_instruction{ Instruction_type::NAME } \
		{ \
			FOR_EACH_SEPARATOR( ASSIGN, SEMICOLON, __VA_ARGS__); \
		} \
		std::string get_name() { return #NAME; } \
		std::string get_argsLine() { return ""; } \
		inline void execute(Routine& routine)

#define Ins0(NAME) \
	using Instruction_##NAME = Instruction<Instruction_type::NAME>; \
	template<> \
	struct Instruction<Instruction_type::NAME> : Base_instruction \
	{ \
		Instruction() : Base_instruction{ Instruction_type::NAME } {} \
		std::string get_name() { return #NAME; } \
		std::string get_argsLine() { return ""; } \
		inline void execute(Routine& routine)

#pragma pack(1)

#define INT(name) (integer, name) 
#define BYTE(name) (byte, name) 

Ins(PUSH_INT, INT(value))
{
	Cell cell;
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
	routine.stack.head[-2].integer = std::pow(routine.stack.head[-2].integer, routine.stack.head[-1].integer);
	routine.stack.head--;
}};

Ins(PRINT, BYTE(arg))
{
	std::cout << routine.stack.cells[arg].integer << std::endl;
}};

Ins0(END)
{
	routine.stop();
}};
