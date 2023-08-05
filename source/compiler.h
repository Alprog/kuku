
#pragma once

#include "instructions.h"
#include "chunk.h"

class translation_module;

class compiler
{
public:
	compiler(translation_module& module);

	void compile();

	template<typename T>
	void spawn(T value)
	{
		chunk.write(value);
	}

	template<instruction_type T>
	void spawn(instruction<T> instruction)
	{
		chunk.write(instruction);
	}

	translation_module& module;
	chunk chunk;
};