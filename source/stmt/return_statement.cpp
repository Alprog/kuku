
#include "return_statement.h"

void stmt::return_statement::parse_internal(Parser& parser)
{
	parser.require(Token_type::Keyword_return);
	expression = parser.parse_expression();
}