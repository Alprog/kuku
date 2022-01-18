
#include "class_statement.h"

void stmt::class_statement::parse_internal(Parser& parser)
{
	parser.require(Token_type::Keyword_class);
	symbol = parser.read_symbol();
}