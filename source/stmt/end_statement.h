
#pragma once

#include "statement.h"

namespace stmt
{
	class end_statement : public statement
	{
		virtual std::u16string get_statement_type() override { return u"end_statement"; }

	public:
		virtual int get_nesting_level() override { return -1; }

	protected:
		virtual void parse_internal(Parser& parser) override;
	};
}
