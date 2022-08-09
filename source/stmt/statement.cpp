
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
		this->end_token = parser.current;
		parser.require_end_of_statement();
		this->is_valid = true;
	}
	catch (unexpected_error ex)
	{
		this->is_valid = false;
		this->error_text = u"unexpected token '" + parser.current->get_source_text() + u"' at " + parser.current->range.start.to_str();
		while (!parser.current->is_end_statement_token()) parser.next(); // panic mode
		this->end_token = parser.current;
		parser.next();
	}

	return this;
}

statement_scope* stmt::statement::get_scope() const
{
	return scope;
}

std::u16string stmt::statement::get_source_text() const
{
	return start_token->document->get_substring(get_full_range());
}

std::u8string stmt::statement::get_hover_text() const
{
	const auto& text = 
		u"**statement:** "_s + get_statement_type() + u"  \r\n" +
		u"**content:** "_s + get_source_text();

	return unicode::to_utf8(text);
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