
#pragma once

#include "block_statement.h"

class Function_statement : public Block_statement
{
	virtual std::u16string get_node_type() override { return u"Function_statement"; }

protected:
	virtual void parse_internal(Parser& parser) override;

	Symbol* symbol;
};