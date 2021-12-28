
#pragma once

#include "statement_node.h"

class Invalid_statement_node : public Statement_node
{
	virtual bool parse_internal(Parser& parser) override { return false; }
};