
#pragma once

#include <vector>
#include "variable.h"

namespace typesystem
{
	class code_block
	{
		std::vector<typesystem::variable> variables;
		std::vector<typesystem::code_block> code_blocks;
	};
};