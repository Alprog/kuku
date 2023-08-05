
#include "return_statement.h"

void stmt::return_statement::parse_internal(parser& parser)
{
	parser.require(token_type::Keyword_return);
	expression = parser.parse_expression();
}