
#pragma once

#include "instruction_flags.h"

class routine;

constexpr size_t INSTRUCTION_COUNT = 256;

using execute_function_ptr = void(*)(routine&);

struct jump_table
{
	static execute_function_ptr execute_function[INSTRUCTION_COUNT];
	static void init();
};
