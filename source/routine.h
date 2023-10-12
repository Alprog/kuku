
#pragma once

#include "stack.h"

class virtual_machine;

class routine
{
public:
	routine(virtual_machine& vm, byte* ip);

	virtual_machine* vm;

	stack stack;

	byte* ip; // instruction pointer
	bool running;

	void run();
	void stop();

	void perform_instruction();

	template<typename T>
	inline T read()
	{
		auto result = *reinterpret_cast<T*>(ip);
		ip += sizeof(T);
		return result;
	}
};