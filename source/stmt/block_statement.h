
#pragma once

#include "statement.h"

namespace stmt
{
	class block_statement : public statement
	{
		virtual std::u16string get_node_type() override { return u"block_statement"; }

	public:
		virtual int get_nesting_level() override { return 1; }

		std::vector<statement*> nested_statements;
		statement* end_statement;
	};
}
