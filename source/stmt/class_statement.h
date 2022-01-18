
#pragma once

#include "block_statement.h"
#include "symbol.h"

namespace stmt
{
	class class_statement : public block_statement
	{
		virtual std::u16string get_statement_type() override { return u"class_statement"; }

	protected:
		virtual void parse_internal(Parser& parser) override;

		Symbol* symbol;
	};
}
