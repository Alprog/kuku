
#include "assign_statement.h"

stmt::assign_statement::assign_statement(std::unique_ptr<ast::expression> expression)
	: lvalue{ std::move(expression) }
{
}

void stmt::assign_statement::parse_internal(Parser& parser)
{
	parser.require(Token_type::Assign_operator);
	rvalue = parser.parse_expression();
}