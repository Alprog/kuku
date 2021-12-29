
#pragma once

#include "statement_node.h"

class Assign_statement_node : public Statement_node
{
	virtual void parse_internal(Parser& parser) override;
};