
#include "statement.h"
#include "unexepected_error.h"

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

	return this;
}

scope* stmt::statement::get_scope()
{
	return scope;
}

void stmt::statement::set_scope(::scope* scope)
{
	this->scope = scope;
}