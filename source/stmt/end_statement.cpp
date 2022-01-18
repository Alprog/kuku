
#include "end_statement.h"

void stmt::end_statement::parse_internal(Parser& parser)
{
	parser.require(Token_type::Keyword_end);
}