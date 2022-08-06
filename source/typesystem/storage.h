
#pragma once

#include <vector>
#include "symbol/type_symbol.h"

namespace typesystem
{
	struct storage
	{
		std::vector<type_symbol*> types;
	};
};