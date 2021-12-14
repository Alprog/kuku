
#pragma once

#include "StatementNode.h"

class InvalidStatementNode : public StatementNode
{
	virtual bool parseInternal(Parser& parser) override { return false; }
};