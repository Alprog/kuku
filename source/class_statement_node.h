
#pragma once

#include "block_statement_node.h"

class ClassStatementNode : public BlockStatementNode
{
protected:
	virtual bool parseInternal(Parser& parser) override;
};