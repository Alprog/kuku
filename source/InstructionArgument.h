
#pragma once

#include <string>
#include <typeinfo>

struct InstructionArgument
{
	virtual std::string getName() = 0;
};

template <typename T>
struct SimpleInstructionArg : InstructionArgument
{
	using ArgumentType = T;

	virtual std::string getName() override
	{
		return typeid(T).name();
	}

	static T load()
	{
		return T();
	}
};