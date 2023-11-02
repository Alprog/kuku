
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

	void spawn(base_instruction instruction)
	{
		current_function->bytecode.instructions.push_back(instruction);
	}

	base_instruction& peek()
	{
		auto& instructions = current_function->bytecode.instructions;
		return instructions[instructions.size() - 1];
	}

	base_instruction pop()
	{
		base_instruction result = peek();
		current_function->bytecode.instructions.pop_back();
		return result;
	}

	template<typename T>
	void compile(T& value);

	chunk chunk;
	rt::function* current_function;
		
	stackable<scope_context> scope_context;

	translation_module& module;
	symbol_table symbol_table;
};
