
#pragma once

#include <stack>
#include "stack.h"
#include "call_frame.h"

class virtual_machine;

class rt::function;

class routine
{
public:
	routine(virtual_machine& vm, rt::function& function);

	virtual_machine& vm;

	std::stack<call_frame> up_frames;

	call_frame call_frame;

	stack stack;

	bool running;

	void run();
	void stop();
	void perform_instruction();

	void push_call_frame(rt::function& function);

	//template<typename T>
	//inline T read()
	//{
	//	auto result = *reinterpret_cast<T*>(ip);
	//	ip += sizeof(T);
	//	return result;
	//}
};