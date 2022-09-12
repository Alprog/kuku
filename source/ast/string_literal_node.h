
#pragma once

#include "single_token_node.h"
#include "string.h"

namespace ast
{
	class string_literal : public single_token_node
	{
	public:
		string_literal(token* token);
	};
}
