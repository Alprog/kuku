
#pragma once

class routine;

constexpr size_t INSTRUCTION_COUNT = 256;

using Execute_function_ptr = void(*)(routine&);
using Get_size_function_ptr = size_t(*)();

struct jump_table
{
	static Execute_function_ptr execute_function[INSTRUCTION_COUNT];
	static Get_size_function_ptr get_size_function[INSTRUCTION_COUNT];

	static void init();
};
