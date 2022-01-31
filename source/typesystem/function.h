
#pragma once

#include <vector>
#include "typesystem/info.h"
#include "typesystem/code_block.h"
#include "typesystem/variable.h"

namespace typesystem
{
	class type;

	class function : public typesystem::info
	{
	public:
		std::u8string name;
		typesystem::type* result_type;
		std::vector<typesystem::type*> arguments_types;

		typesystem::code_block* code_block;
	};
};