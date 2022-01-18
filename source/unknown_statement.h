
#pragma once

#include "stmt/statement.h"
#include "unexepected_error.h"

class unknown_statement : public stmt::statement
{
	virtual std::u16string get_statement_type() override { return u"unknown_statement"; }

	virtual void parse_internal(Parser& parser) override 
	{
		throw unexpected_error();
	}
};