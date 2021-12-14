
#pragma once

#include "BlockStatementNode.h"

class FunctionStatementNode : public BlockStatementNode
{
protected:
	virtual bool parseInternal(Parser& parser) override;
};