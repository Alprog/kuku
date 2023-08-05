
#include "end_statement.h"

void stmt::end_statement::parse_internal(parser& parser)
{
	parser.require(token_type::Keyword_end);
}