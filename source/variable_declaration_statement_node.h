
#pragma once

#include "statement_node.h"
#include "parser.h"

class VariableDeclarationStatementNode : public StatementNode
{
public:
	virtual bool parseInternal(Parser& parser) override;
};