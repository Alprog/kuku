
#pragma once

#include "Instructions.h"
#include "Chunk.h"

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

	template<Instruction_type T>
	void spawn(Instruction<T> instruction)
	{
		chunk.write(instruction);
	}

	translation_module& module;
	Chunk chunk;
};