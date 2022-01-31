
#pragma once

#include <vector>
#include "typesystem/type.h"

namespace typesystem
{
	struct storage
	{
		std::vector<typesystem::type*> types;
	};
};