
#pragma once

#include "statement_node.h"

class End_statement_node : public Statement_node
{
public:
	virtual int get_nesting_level() override { return -1; }

protected:
	virtual void parse_internal(Parser& parser) override;
};