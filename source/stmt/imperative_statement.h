
#pragma once

#include "statement.h"

namespace stmt
{
	class imperative_statement : public stmt::statement
	{
	public:
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }
		virtual scope_type get_inner_scope_type() const override { return scope_type::none; }
	};
}
