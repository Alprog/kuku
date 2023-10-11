
#pragma once

#include "instructions.h"
#include "bytecode.h"
#include "symbol_table.h"

class translation_module;

class compiler
{
public:
	compiler(translation_module& module);

	void compile();

	template<typename T>
	void spawn(T value)
	{
		bytecode.write(value);
	}

	template<instruction_type T>
	void spawn(instruction<T> instruction)
	{
		bytecode.write(instruction);
	}

	translation_module& module;
	symbol_table symbol_table;
	bytecode bytecode;
};