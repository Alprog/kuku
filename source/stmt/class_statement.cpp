
#include "class_statement.h"
#include "symbol_reference.h"

void stmt::class_statement::parse_internal(parser& parser)
{
	parser.require(token_type::Keyword_class);
	parse_symbol(parser);
}

void stmt::class_statement::define_symbols(statement_scope* scope)
{
	scope->define_symbol(symbol);
}