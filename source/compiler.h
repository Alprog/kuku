
#pragma once

#include "instructions.h"
#include "bytecode.h"
#include "symbol_table.h"
#include "chunk.h"
#include "stackable.h"
#include "scope_context.h"

class translation_module;
 
class compiler
{
public:
	compiler(translation_module& module);

	void compile();
	void start_new_function();
	void enter_scope();
	void exit_scope();

	void jump_here(int jump_place);

	template<instruction_type T>
	void spawn(instruction<T> instruction)
	{
		current_function->bytecode.write(instruction);
	}

	template<typename T>
	void compile(T& value);

	chunk chunk;
	rt::function* current_function;
	
	stackable<scope_context> scope_context;

	translation_module& module;
	symbol_table symbol_table;
};
