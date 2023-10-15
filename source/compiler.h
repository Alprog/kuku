
#pragma once

#include "instructions.h"
#include "bytecode.h"
#include "symbol_table.h"
#include "chunk.h"

class translation_module;
 
namespace stmt
{
	class expression_statement;
}

class compiler
{
public:
	compiler(translation_module& module);

	void compile();
	void start_new_function();

	template<instruction_type T>
	void spawn(instruction<T> instruction)
	{
		current_function->bytecode.write(instruction);
	}

	template<typename T>
	void compile_impl(T value);

	chunk chunk;
	rt::function* current_function;
	translation_module& module;
	symbol_table symbol_table;
};
