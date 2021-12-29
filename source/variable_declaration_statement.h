
#pragma once

#include "statement.h"
#include "parser.h"

class Variable_declaration_statement : public Statement
{
	virtual std::u16string get_node_type() override { return u"Variable_declaration_statement"; }

public:
	virtual void parse_internal(Parser& parser) override;

	Symbol* symbol;
};