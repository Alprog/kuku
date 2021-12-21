
#pragma once

#include "statement_node.h"

class AssignStatementNode : public StatementNode
{
	virtual bool parseInternal(Parser& parser) override;
};