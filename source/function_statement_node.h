
#pragma once

#include "block_statement_node.h"

class Function_statement_node : public Block_statement_node
{
protected:
	virtual bool parse_internal(Parser& parser) override;
};