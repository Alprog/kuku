
#pragma once

#include "statement_node.h"

class Assign_statement_node : public Statement_node
{
	virtual bool parse_internal(Parser& parser) override;
};