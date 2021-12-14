
#pragma once

#include "StatementNode.h"

class BlockStatementNode : public StatementNode
{
public:
	virtual int getNestingLevel() override { return 1; }

	std::vector<StatementNode*> nestedStatements;
	StatementNode* endStatement;
};