
#include "function_statement_node.h"

bool Function_statement_node::parse_internal(Parser& parser)
{
	parser.require_keyword(u"function");

	
	parser.require(Token_type::Identifier);

	parser.require(Token_type::Open_parenthesis);
	parser.require(Token_type::Close_parenthesis);

	if (parser.match_end_of_statement()) return true;

	parser.require(Token_type::Semicolon);
	parser.require(Token_type::Identifier);

	if (parser.match_end_of_statement()) return true;
	
	return false;
}