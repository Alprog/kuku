
#include "class_statement.h"
#include "symbol_reference.h"

stmt::class_statement::class_statement()
	: scope{ this }
	, definition{ nullptr }
	, type_info{ nullptr }
{
}

void stmt::class_statement::parse_internal(Parser& parser)
{
	parser.require(Token_type::Keyword_class);
	definition = parser.read_symbol_reference();
}

void stmt::class_statement::define_symbols(statement_scope*& scope)
{
	type_info = new typesystem::type();
	type_info->name = this->definition->token->get_source_text();

	auto definition_symbol = new symbol(type_info, definition);
	definition_symbol->inner_scope = &this->scope;
	scope = definition_symbol->inner_scope;
} 