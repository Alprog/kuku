#pragma once

#include "rt/function.h"

union cell;

struct call_frame
{
	explicit call_frame(rt::function& function, cell* stack);
	
	rt::function* function;
	base_instruction* ip;
	
	union
	{
		struct
		{
			cell* stack;
			cell* constants;
		};
		cell* ptr[2];
	};
};