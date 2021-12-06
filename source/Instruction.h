
#pragma once

#include "InstructionType.h"
#include "types.h"
#include "string.h"
#include <vector>
#include "Routine.h"

using PerformFunctionPtr = void(*)(Routine&);

struct Instruction
{
	InstructionType id;
	std::string name;
	std::vector<std::string> arguments;
	PerformFunctionPtr performFunction;

	Instruction() = default;

	Instruction(InstructionType id, std::string name)
		: id{ id }
		, name{ name }
		, performFunction{ nullptr }
	{
	}

	template <typename... Args>
	using PerformHelperFunction = void(*)(Routine& routine, Args... args);

	template<typename HelperClass, typename... Args>
	void reg(HelperClass, PerformHelperFunction<Args...>);
};

struct InstructionSet
{
	static void Init();

	static Instruction Instructions[256];
	static PerformFunctionPtr PerformFunctions[256];
};

template<typename HelperClass, typename... Args>
void Instruction::reg(HelperClass, PerformHelperFunction<Args...>)
{
	struct local
	{
		static std::vector<std::string> getArguments()
		{
			return { typeid(Args).name()... };
		}

		static inline void perform(Routine& routine)
		{
			HelperClass::body(routine, routine.read<Args>()...);
		}
	};

	arguments = local::getArguments();
	performFunction = local::perform;

	InstructionSet::PerformFunctions[(byte)id] = performFunction;
}
