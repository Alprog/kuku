
#include "function_statement.h"

void stmt::function_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_function);
	parse_symbol(parser);
	parser.require(token_type::Open_parenthesis);
	// arguments
	parser.require(token_type::Close_parenthesis);

	CHECK_END_OF_STATEMENT

	parser.require(token_type::Colon);
	parser.require(token_type::Identifier);
}

void stmt::function_statement::define_symbols(statement_scope* scope)
{
	scope->define_symbol(symbol);
}