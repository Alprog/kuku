
#pragma once

#include "Stack.h"

class Routine
{
public:
	Routine(byte* ip);

	Stack stack;

	byte* ip; // instruction pointer

	void run();

	void performInstruction();

private:
	template<typename T>
	T read()
	{
		auto result = *reinterpret_cast<T*>(ip);
		ip += sizeof(T);
		return result;
	}
};