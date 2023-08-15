
#pragma once

#include "types.h"

struct instruction_arg_meta_base
{
	virtual void print_value(byte*& pointer) = 0;
};

template <typename T>
struct instruction_arg_meta : public instruction_arg_meta_base
{
	static instruction_arg_meta* get_instance()
	{
		static instruction_arg_meta instance;
		return &instance;
	}

	void print_value(byte*& pointer) override
	{
		//printf( *reinterpret_cast<T*>(pointer) );
		//pointer += sizeof(T);
	}
};