
#pragma once

#include "statement.h"

namespace stmt
{
	class block_statement : public statement
	{
		virtual std::u16string get_statement_type() override { return u"block_statement"; }
		
	public:
		virtual int get_nesting_level() override { return 1; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }
		virtual scope_type get_inner_scope_type() const override { return scope_type::block_body; }

		std::vector<statement*> nested_statements;
		statement* end_statement;
	};
}
