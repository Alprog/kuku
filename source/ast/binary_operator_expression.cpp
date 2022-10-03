
#include "binary_operator_expression.h"
#include "compiler.h"

ast::binary_operator_expression::binary_operator_expression(std::unique_ptr<expression> left, binary_operator& op, std::unique_ptr<expression> right)
	: left{ std::move(left) }
	, op{ op }
	, right{ std::move(right) }
{
}

void ast::binary_operator_expression::semantic_analyze(stmt::statement& statement)
{
	left->semantic_analyze(statement);
	right->semantic_analyze(statement);

	/* TODO: analyze is it applicable to do operation */
}

void ast::binary_operator_expression::compile(compiler& compiler)
{
	left->compile(compiler);
	right->compile(compiler);

	switch (op.token_type)
	{
		case Token_type::Plus_operator:
			compiler.spawn(Instruction_INT_ADD{});
			break;

		case Token_type::Minus_operator:
			compiler.spawn(Instruction_INT_SUB{});
			break;

		case Token_type::Multiply_Operator:
			compiler.spawn(Instruction_INT_MULTIPLY{});
			break;

		case Token_type::Divide_Operator:
			compiler.spawn(Instruction_INT_DIVIDE{});
			break;
			
		case Token_type::Exponent_operator:
			compiler.spawn(Instruction_INT_POWER{});
			break;

		default:
			throw std::exception("not implemented");
	}

	
}