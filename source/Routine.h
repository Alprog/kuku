
#pragma once

#include "Stack.h"

class Routine
{
public:
	Stack stack;

	byte* ip; // instruction pointer

	void run();

	void performInstruction();
};