
#include "jump_table.h"
#include "instructions.h"
#include <cassert>

execute_function_ptr jump_table::execute_function[INSTRUCTION_COUNT];
get_info_function_ptr jump_table::get_info_function[INSTRUCTION_COUNT];

//------------------------------------------------------------------------------

template <typename T>
inline void execute_instruction(routine& routine)
{
	reinterpret_cast<T*>(routine.call_frame.ip++)->execute(routine);
}

template <>
inline void execute_instruction<instruction_JUMP>(routine& routine)
{
	reinterpret_cast<instruction_JUMP*>(routine.call_frame.ip)->execute(routine);
}

template <>
inline void execute_instruction<instruction_IFJUMP>(routine& routine)
{
	reinterpret_cast<instruction_IFJUMP*>(routine.call_frame.ip)->execute(routine);
}

template <typename T>
inline instruction_info* get_info()
{
	static instruction_info info = T::create_info();
	return &info;
}

template <int Index, int BaseIndex = Index, instruction_mode mode = instruction_mode::RR>
void register_instruction_internal()
{
	assert(get_name((opcode)Index).starts_with(get_name((opcode)BaseIndex)));

	using instructionT = instruction<(opcode)BaseIndex, mode>;
	jump_table::execute_function[Index] = execute_instruction<instructionT>;
	jump_table::get_info_function[Index] = get_info<instructionT>;
}

constexpr bool contains(instruction_args mask, instruction_args flag)
{
	return (mask & flag) == flag;
}

template <int I>
void register_instruction()
{
	using instructionT = instruction<(opcode)I>;
	if constexpr (instructionT::args != instruction_args::invalid)
	{
		register_instruction_internal<I>();
	}
	if constexpr (contains(instructionT::args, instruction_args::MB))
	{
		register_instruction_internal<I + 1, I, instruction_mode::KR>();
	}
	if constexpr (contains(instructionT::args, instruction_args::MC))
	{
		register_instruction_internal<I + 2, I, instruction_mode::RK>();
	}
	if constexpr (contains(instructionT::args, instruction_args::M2))
	{
		register_instruction_internal<I + 3, I, instruction_mode::KK>();
	}
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



