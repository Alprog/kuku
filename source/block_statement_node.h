
#pragma once

#include "statement_node.h"

class Block_statement_node : public Statement_node
{
public:
	virtual int get_nesting_level() override { return 1; }

	std::vector<Statement_node*> nested_statements;
	Statement_node* end_statement;
};