
#pragma once

#include "symboled_statement.h"
#include "typesystem/function.h"

namespace stmt
{
	class function_statement : public scoped_symboled_statement
	{
	public:
		function_statement();

		virtual std::u16string get_statement_type() override { return u"function_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::class_body; }
		virtual scope_type get_inner_scope_type() const override { return scope_type::function_body; }
		
		virtual void define_symbols(statement_scope*& scope) override;

	protected:
		virtual void parse_internal(Parser& parser) override;

		typesystem::function function_info;
	};
}
