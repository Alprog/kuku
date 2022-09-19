
#include "expression_statement.h"

#include "ast/expression.h"

stmt::expression_statement::expression_statement(std::unique_ptr<ast::expression> expression)
	: expression{ std::move(expression) }
{
}

void stmt::expression_statement::parse_internal(Parser& parser)
{
	return;
}

void stmt::expression_statement::compile(compiler& compiler)
{
	expression->compile(compiler);
}