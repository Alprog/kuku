
#pragma once

#include "statement_node.h"
#include "unexepected_error.h"

class Invalid_statement_node : public Statement_node
{
	virtual void parse_internal(Parser& parser) override 
	{
		throw Unexpected_error();
	}
};