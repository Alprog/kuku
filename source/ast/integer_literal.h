
#pragma once

#include "single_token_node.h"

namespace ast
{
	class integer_literal : single_token_node
	{
	public:
		integer_literal(token* token);

		int value;
	};
}
