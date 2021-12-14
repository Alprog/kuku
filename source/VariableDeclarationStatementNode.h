
#pragma once

#include "StatementNode.h"
#include "Parser.h"

class VariableDeclarationStatementNode : public StatementNode
{
public:
	virtual bool parseInternal(Parser& parser) override;
};