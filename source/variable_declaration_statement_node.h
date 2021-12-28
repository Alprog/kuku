
#pragma once

#include "statement_node.h"
#include "parser.h"

class Variable_declaration_statement_node : public Statement_node
{
public:
	virtual bool parse_internal(Parser& parser) override;
};