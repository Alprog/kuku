#pragma once

#include <vector>

struct scope_context
{
	scope_context(int start_place, int stack_size, bool is_loop)
		: start_place{ start_place }
		, stack_size{ stack_size }
		, is_loop{ is_loop }
	{
	}

	int start_place;
	int stack_size;
	bool is_loop;
	std::vector<int> jump_to_end_places;
};