#pragma once

#include "symbol_table.h"
#include "chunk.h"
#include "stackable.h"
#include "scope_context.h"
#include "inline_operand.h"
#include "stack_ex.h"

class translation_module;
 
class compiler
{
public:
	compiler(translation_module& module);

	void compile();
	void start_new_function();
	void enter_scope(bool is_loop = false);
	void enter_loop_scope();
	void exit_scope();

	void jump_here(int jump_place);

	void spawn(base_instruction instruction);

	base_instruction& peek();
	base_instruction pop();

	inline_operand get_top_operand();
	int get_current_place();

	template<typename T>
	void compile(T& value);

	chunk chunk;
	rt::function* current_function;

	stack_ex<scope_context> scope_contexts;
	scope_context& scope_context() { return scope_contexts.top(); }

	translation_module& module;
	symbol_table symbol_table;
};
