
#pragma once

#include "block_statement.h"

namespace stmt
{
	class function_statement : public block_statement
	{
		virtual std::u16string get_node_type() override { return u"function_statement"; }

	protected:
		virtual void parse_internal(Parser& parser) override;

		Symbol* symbol;
	};
}
