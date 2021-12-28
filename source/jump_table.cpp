
#include "jump_table.h"
#include "instructions.h"

Execute_function_ptr Jump_table::execute_function[INSTRUCTION_COUNT];
Get_size_function_ptr Jump_table::get_size_function[INSTRUCTION_COUNT];

template <typename T>
inline void read_and_execute_instruction(Routine& routine)
{
	auto instruction = reinterpret_cast<T*>(routine.ip);
	instruction->execute(routine);
	routine.ip += sizeof(T);
}

template <typename T>
inline size_t get_size()
{
	return sizeof(T);
}

template <int I>
void register_instruction()
{
	using InstructionT = Instruction<(Instruction_type)I>;
	Jump_table::execute_function[I] = read_and_execute_instruction<InstructionT>;
	Jump_table::get_size_function[I] = get_size<InstructionT>;
}

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

void Jump_table::init()
{
	register_instruction_recursive<255>();
}
