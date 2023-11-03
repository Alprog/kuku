#pragma once

#include "rt/function.h"

union cell;

struct call_frame
{
	explicit call_frame(rt::function& function, cell* start);
	
	rt::function* function;
	base_instruction* ip;
	cell* start;
};