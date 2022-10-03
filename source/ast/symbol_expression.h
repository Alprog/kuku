
#pragma once

#include "expression.h"
#include "Token.h"

namespace ast
{
	class symbol_expression : public expression
	{
	public:
		symbol_expression(token& token);
		virtual void compile(compiler& compiler) override;

		symbol_reference reference;
	};
}
