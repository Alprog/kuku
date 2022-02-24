
#include "class_statement.h"
#include "symbol_reference.h"

stmt::class_statement::class_statement()
	: scoped_symboled_statement{ &type_info }
{
}

void stmt::class_statement::parse_internal(Parser& parser)
{
	parser.require(Token_type::Keyword_class);
	definition_reference = *parser.read_symbol_reference();
	definition_symbol.name = definition_reference.token->get_source_text();
	type_info.name = definition_reference.token->get_source_text();
}

void stmt::class_statement::define_symbols(statement_scope*& scope)
{
	scope->define_symbol(&definition_symbol);

	
	scope = &inner_scope;
}