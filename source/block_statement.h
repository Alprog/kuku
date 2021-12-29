
#pragma once

#include "statement.h"

class Block_statement : public Statement
{
	virtual std::u16string get_node_type() override { return u"Block_statement"; }

public:
	virtual int get_nesting_level() override { return 1; }

	std::vector<Statement*> nested_statements;
	Statement* end_statement;
};