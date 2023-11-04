
#include "jump_table.h"
#include "instructions.h"

execute_function_ptr jump_table::execute_function[INSTRUCTION_COUNT];
get_info_function_ptr jump_table::get_info_function[INSTRUCTION_COUNT];

//------------------------------------------------------------------------------

template <typename T>
inline void execute_instruction(routine& routine)
{
	reinterpret_cast<T*>(routine.call_frame.ip)->execute(routine);
}	

template <typename T>
inline instruction_info* get_info()
{
	static instruction_info info = T::create_info();
	return &info;
}

template <int I>
void register_instruction()
{
	using instructionT = instruction<(instruction_type)I>;
	jump_table::execute_function[I] = execute_instruction<instructionT>;
	jump_table::get_info_function[I] = get_info<instructionT>;
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



