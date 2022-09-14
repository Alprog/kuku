
#pragma once

#include "Instructions.h"

class translation_module;

class compiler
{
public:
	compiler(translation_module& module);

	void compile();

	template<typename T>
	void spawn(T t)
	{

	}

	template<Instruction_type T>
	void spawn(Instruction<T> Instruction)
	{
	}

	translation_module& module;
};