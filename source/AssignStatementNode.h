
#pragma once

#include "StatementNode.h"

class AssignStatementNode : public StatementNode
{
	virtual bool parseInternal(Parser& parser) override;
};