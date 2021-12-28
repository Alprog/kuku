
#include "end_statement_node.h"

bool End_statement_node::parse_internal(Parser& parser)
{
	if (parser.match_keyword(u"end"))
	{
		if (parser.match_end_of_statement()) return true;
	}
	return false;
}