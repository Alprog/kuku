
#pragma once

#include "stmt/statement.h"
#include "unexepected_error.h"

namespace stmt
{
	class unknown_statement : public stmt::statement
	{
		virtual std::u16string get_node_type() override { return u"unknown_statement"; }

		virtual void parse_internal(Parser& parser) override
		{
			throw unexpected_error();
		}
	};
}
