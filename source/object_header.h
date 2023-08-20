
#pragma once

#include <types.h>
#include <vector>
#include "guid.h"
#include "cell.h"

struct object_header
{
	object_header(class_index class_index);
	void destroy();

	class_index class_index;
	guid guid;
	cell* data;
};

static_assert(sizeof(object_header) == 16);