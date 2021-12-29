
#include "statement_node.h"
#include "unexepected_error.h"

Statement_node* Statement_node::init(Parser& parser)
{
	this->start_token = parser.current;

	try
	{
		this->is_valid = parse_internal(parser);
	}
	catch (Unexpected_error ex)
	{
		this->is_valid = false;
		this->error_text = u"unexpected token '" + parser.current->get_source_text() + u"' at " + parser.current->range.start.to_str();
		while (!parser.current->is_end_statement_token()) parser.next(); // panic mode
		parser.next();
	}

	return this;
}

int Statement_node::get_nesting_level()
{
	return 0;
}