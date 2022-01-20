
#pragma once

#include "statement.h"

namespace stmt
{
	class end_statement : public statement
	{
		virtual std::u16string get_statement_type() override { return u"end_statement"; }

	public:
		virtual scope_type get_allowed_scopes() const override { return scope_type::end_scopes; }
		virtual scope_type get_inner_scope_type() const override { return scope_type::none; }

	protected:
		virtual void parse_internal(Parser& parser) override;
	};
}
