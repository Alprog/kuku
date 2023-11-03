
#include "jump_table.h"
#include "instructions.h"

execute_function_ptr jump_table::execute_function[INSTRUCTION_COUNT];

//------------------------------------------------------------------------------

template <typename T>
inline void read_and_execute_instruction(routine& routine)
{
	reinterpret_cast<T*>(routine.call_frame.ip)->execute(routine);
}	

template <int I>
void register_instruction()
{
	using instructionT = instruction<(instruction_type)I>;
	jump_table::execute_function[I] = read_and_execute_instruction<instructionT>;
};

template <int I>
void register_instruction_recursive()
{
	register_instruction<I>();
	register_instruction_recursive<I - 1>();
}

template <>
void register_instruction_recursive<0>()
{
	register_instruction<0>();
}

void jump_table::init()
{
	register_instruction_recursive<255>();
}

//------------------------------------------------------------------------------



