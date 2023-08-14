
#pragma once

#include "types.h"

struct instruction_arg_base
{
	virtual void print_value(byte*& pointer) = 0;
};

template <typename T>
struct instruction_arg : public instruction_arg_base
{
	void print_value(byte*& pointer) override
	{
		//printf( *reinterpret_cast<T*>(pointer) );
		//pointer += sizeof(T);
	}
};