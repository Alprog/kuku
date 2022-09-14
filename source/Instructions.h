
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

Ins(INT_SET, INT(value))
{
	Cell cell;
	cell.integer = value;
	routine.stack.push(cell);
}};

Ins(INT_ADD, BYTE(arg1), BYTE(arg2), BYTE(out))
{
	routine.stack.cells[out].integer = routine.stack.cells[arg1].integer + routine.stack.cells[arg2].integer;
}};

Ins(PRINT, BYTE(arg))
{
	std::cout << routine.stack.cells[arg].integer << std::endl;
}};

Ins0(END)
{
	routine.stop();
}};
