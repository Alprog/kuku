
#pragma once

#include "statement_node.h"

class InvalidStatementNode : public StatementNode
{
	virtual bool parseInternal(Parser& parser) override { return false; }
};