
#pragma once

#include "stmt/statement.h"
#include "unexepected_error.h"

namespace stmt
{
	class unknown_statement : public stmt::statement
	{
		virtual std::u16string get_statement_type() override { return u"unknown_statement"; }

		virtual scope_type get_allowed_scopes() const override { return scope_type::any; }
		virtual scope_type get_inner_scope_type() const override { return scope_type::none; }

		virtual void parse_internal(Parser& parser) override
		{
			throw unexpected_error();
		}
	};
}
