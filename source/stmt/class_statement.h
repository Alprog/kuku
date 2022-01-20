
#pragma once

#include "block_statement.h"
#include "symbol.h"

namespace stmt
{
	class class_statement : public block_statement
	{
	public:
		virtual std::u16string get_statement_type() override { return u"class_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::module_root; }
		virtual scope_type get_inner_scope_type() const override { return scope_type::class_body; }

	protected:
		virtual void parse_internal(Parser& parser) override;

		Symbol* symbol;
	};
}
