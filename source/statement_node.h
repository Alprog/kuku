
#pragma once

#include "syntax_node.h"
#include "token.h"
#include "parser.h"

#define CHECK_END_OF_STATEMENT if (parser.current->is_end_statement_token()) return;

class Statement_node : Syntax_node
{
public:
	Token* start_token;
	Token* end_token;

	bool is_valid;
	std::u16string error_text;

	Statement_node* init(Parser& parser);

	virtual int get_nesting_level();

protected:
	virtual void parse_internal(Parser& parser) = 0;
};