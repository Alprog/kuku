
#pragma once

#include <vector>
#include "typesystem/info.h"
#include "typesystem/field.h"
#include "typesystem/function.h"

namespace typesystem
{
	struct type : public typesystem::info
	{
	public:
		std::u16string name;
		typesystem::type* parent_type;

		std::vector<typesystem::field*> fields;
		std::vector<typesystem::function*> functions;
	};
};
