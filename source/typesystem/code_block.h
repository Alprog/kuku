
#pragma once

#include <vector>
#include "symbol/variable_symbol.h"

namespace typesystem
{
	class code_block
	{
		std::vector<variable_symbol> variables;
		std::vector<typesystem::code_block> code_blocks;
	};
};