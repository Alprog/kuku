
#pragma once

#include "statement.h"

namespace stmt
{
	class assign_statement : public stmt::statement
	{
		virtual std::u16string get_statement_type() const override { return u"assign_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }

		virtual void parse_internal(Parser& parser) override;
	};
}
