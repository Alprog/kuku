
#include "class_statement.h"

void stmt::class_statement::parse_internal(Parser& parser)
{
	parser.require(Token_type::Keyword_class);
	reference = parser.read_symbol_reference();
}

void stmt::class_statement::define_symbols()
{

}