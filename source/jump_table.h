
#pragma once

class Routine;

constexpr size_t INSTRUCTION_COUNT = 256;

using Execute_function_ptr = void(*)(Routine&);
using Get_size_function_ptr = size_t(*)();

struct Jump_table
{
	static Execute_function_ptr execute_function[INSTRUCTION_COUNT];
	static Get_size_function_ptr get_size_function[INSTRUCTION_COUNT];

	static void init();
};
