
#pragma once

#include "block_statement_node.h"

class FunctionStatementNode : public BlockStatementNode
{
protected:
	virtual bool parseInternal(Parser& parser) override;
};