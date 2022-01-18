
#pragma once

#include "statement.h"

namespace stmt
{
	class assign_statement : public statement
	{
		virtual std::u16string get_node_type() override { return u"assign_statement"; }

		virtual void parse_internal(Parser& parser) override;
	};
}
