
#pragma once

#include "block_statement.h"

class Class_statement : public Block_statement
{
	virtual std::u16string get_node_type() override { return u"Class_statement"; }

protected:
	virtual void parse_internal(Parser& parser) override;
};