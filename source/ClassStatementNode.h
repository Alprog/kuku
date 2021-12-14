
#pragma once

#include "BlockStatementNode.h"

class ClassStatementNode : public BlockStatementNode
{
protected:
	virtual bool parseInternal(Parser& parser) override;
};