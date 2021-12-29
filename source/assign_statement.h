
#pragma once

#include "statement.h"

class Assign_statement : public Statement
{
	virtual std::u16string get_node_type() override { return u"Assign_statement"; }

	virtual void parse_internal(Parser& parser) override;
};