
#pragma once

#include "StatementNode.h"

class EndStatementNode : public StatementNode
{
public:
	virtual int getNestingLevel() override { return -1; }

protected:
	virtual bool parseInternal(Parser& parser) override;
};