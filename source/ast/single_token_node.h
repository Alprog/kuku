
#pragma once

#include "node.h"
#include "token.h"

namespace ast
{
	class single_token_node : public ast::node
	{
	public:
		token* node_token;
	};
}
