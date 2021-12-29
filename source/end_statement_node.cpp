
#include "end_statement_node.h"

void End_statement_node::parse_internal(Parser& parser)
{
	parser.require_keyword(u"end");
}