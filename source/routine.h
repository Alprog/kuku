
#pragma once

#include "Stack.h"

class routine
{
public:
	routine(byte* ip);

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