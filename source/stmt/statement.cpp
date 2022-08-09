
#include "statement.h"
#include "unexepected_error.h"

stmt::statement::~statement()
{
}

stmt::statement* stmt::statement::init(Parser& parser)
{
	this->start_token = parser.current;

	try
	{
		parse_internal(parser);
		parser.require_end_of_statement();
		this->is_valid = true;
	}
	catch (unexpected_error ex)
	{
		this->is_valid = false;
		this->error_text = u"unexpected token '" + parser.current->get_source_text() + u"' at " + parser.current->range.start.to_str();
		while (!parser.current->is_end_statement_token()) parser.next(); // panic mode
		parser.next();
	}

	this->end_token = parser.current;

	return this;
}

statement_scope* stmt::statement::get_scope() const
{
	return scope;
}

std::u8string stmt::statement::get_hover_text() const
{
	const auto& type_string = get_statement_type();
	return u8"**statement:** "_s + unicode::to_utf8(type_string);
}

lsp::range stmt::statement::get_full_range() const
{
	return lsp::range(start_token->range.start, end_token->range.end);
}

void stmt::statement::set_scope(statement_scope* scope)
{
	this->scope = scope;
}

void stmt::statement::define_symbols(statement_scope* scope)
{

}