
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
		types.push(instruction.type);
		//current_function->bytecode.align(8);
	}

	template<instruction_type T>
	instruction<T>& peek()
	{
		auto& bytes = current_function->bytecode.bytes;
		auto start = bytes.size() - sizeof(instruction<T>);
		return *reinterpret_cast<instruction<T>*>(&bytes[start]);
	}

	template<instruction_type T>
	instruction<T> pop()
	{
		auto& bytes = current_function->bytecode.bytes;
		auto new_size = bytes.size() - sizeof(instruction<T>);
		instruction<T> result = *reinterpret_cast<instruction<T>*>(&bytes[new_size]);
		bytes.resize(new_size);
		return result;
	}

	template<typename T>
	void compile(T& value);

	chunk chunk;
	rt::function* current_function;
		
	stackable<scope_context> scope_context;

	std::stack<instruction_type> types;

	translation_module& module;
	symbol_table symbol_table;
};
