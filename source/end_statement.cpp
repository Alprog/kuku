
#include "end_statement.h"

void End_statement::parse_internal(Parser& parser)
{
	parser.require(Token_type::Keyword_end);
}