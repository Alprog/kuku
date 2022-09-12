
#pragma once

#include "single_token_node.h"

namespace ast
{
	class binary_operator : public single_token_node
	{
	public:
		binary_operator(token* token);
	};
}
