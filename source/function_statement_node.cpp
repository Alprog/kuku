
#include "function_statement_node.h"

void Function_statement_node::parse_internal(Parser& parser)
{
	parser.require_keyword(u"function");
	parser.require(Token_type::Identifier);
	parser.require(Token_type::Open_parenthesis);
	// arguments
	parser.require(Token_type::Close_parenthesis);

	CHECK_END_OF_STATEMENT

	parser.require(Token_type::Colon);
	parser.require(Token_type::Identifier);
}