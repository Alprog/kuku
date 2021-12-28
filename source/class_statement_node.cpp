
#include "class_statement_node.h"

bool Class_statement_node::parse_internal(Parser& parser)
{
	if (parser.match_keyword(u"class"))
	{
		if (parser.match(Token_type::Identifier))
		{
			if (parser.match_end_of_statement()) return true;
		}
	}
	return false;
}