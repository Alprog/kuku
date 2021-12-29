
#pragma once

#include "statement.h"

class End_statement : public Statement
{
	virtual std::u16string get_node_type() override { return u"End_statement"; }

public:
	virtual int get_nesting_level() override { return -1; }

protected:
	virtual void parse_internal(Parser& parser) override;
};