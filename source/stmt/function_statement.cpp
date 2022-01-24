
#include "function_statement.h"

void stmt::function_statement::parse_internal(Parser& parser)
{
	parser.require(Token_type::Keyword_function);
	reference = parser.read_symbol_reference();
	parser.require(Token_type::Open_parenthesis);
	// arguments
	parser.require(Token_type::Close_parenthesis);

	CHECK_END_OF_STATEMENT

	parser.require(Token_type::Colon);
	parser.require(Token_type::Identifier);
}