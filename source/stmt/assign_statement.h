
#pragma once

#include "imperative_statement.h"

namespace stmt
{
	class assign_statement : public imperative_statement
	{
		virtual std::u16string get_statement_type() override { return u"assign_statement"; }

		virtual void parse_internal(Parser& parser) override;
	};
}
