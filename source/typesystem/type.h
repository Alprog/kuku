
#pragma once

#include <vector>
#include "typesystem/field.h"
#include "typesystem/function.h"

namespace typesystem
{
	struct type
	{
		std::vector<typesystem::field> fields;
		std::vector<typesystem::function> functions;
	};
};