
#pragma once

#include <memory>
#include "operand.h"
#include "binary_operator.h"

namespace ast
{
	class binary_operator_expression : public operand
	{
	public:
		binary_operator_expression(std::unique_ptr<expression> left, binary_operator& op, std::unique_ptr<expression> right);

		std::unique_ptr<expression> left;
		binary_operator& op;
		std::unique_ptr<expression> right;

		virtual void compile(compiler& compiler) override;
	};
}
