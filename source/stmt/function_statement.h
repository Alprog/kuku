
#pragma once

#include "block_statement.h"

namespace stmt
{
	class function_statement : public block_statement
	{
		virtual std::u16string get_statement_type() override { return u"function_statement"; }

	protected:
		virtual scope_type get_allowed_scopes() const override { return scope_type::class_body; }
		virtual scope_type get_inner_scope_type() const override { return scope_type::function_body; }
		
		virtual void parse_internal(Parser& parser) override;

		symbol_reference* reference;
	};
}
