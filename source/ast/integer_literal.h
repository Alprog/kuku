
#pragma once

#include "expression.h"
#include "single_token_node.h"

namespace ast
{
	class integer_literal : public expression
	{
	public:
		integer_literal(token& token);
		virtual void compile(compiler& compiler) override;

		integer value;
	};
}
