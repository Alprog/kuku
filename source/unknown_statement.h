
#pragma once

#include "statement.h"
#include "unexepected_error.h"

class Unknown_statement : public Statement
{
	virtual std::u16string get_node_type() override { return u"Unknown_statement"; }

	virtual void parse_internal(Parser& parser) override 
	{
		throw Unexpected_error();
	}
};