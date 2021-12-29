
#include "class_statement_node.h"

void Class_statement_node::parse_internal(Parser& parser)
{
	parser.require_keyword(u"class");
	parser.require(Token_type::Identifier);
}