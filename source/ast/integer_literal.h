
#pragma once

#include "operand.h"
#include "single_token_node.h"

namespace ast
{
	class integer_literal : public single_token_node, public operand
	{
	public:
		integer_literal(token* token);
		virtual void compile(compiler& compiler) override;

		integer value;
	};
}
