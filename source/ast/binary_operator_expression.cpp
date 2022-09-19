
#include "binary_operator_expression.h"
#include "compiler.h"

ast::binary_operator_expression::binary_operator_expression(std::unique_ptr<expression> left, binary_operator& op, std::unique_ptr<expression> right)
	: left{ std::move(left) }
	, op{ op }
	, right{ std::move(right) }
{
}

void ast::binary_operator_expression::compile(compiler& compiler)
{
	left->compile(compiler);

	compiler.spawn(Instruction_INT_ADD{});

	right->compile(compiler);
}