
#pragma once

#include "scoped_symboled_statement.h"
#include "symbol/function_symbol.h"

namespace stmt
{
	class function_statement : public scoped_symboled_statement<scope_type::function_body, function_symbol>
	{
	public:
		virtual std::u16string get_statement_type() override { return u"function_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::class_body; }
		
		virtual void define_symbols(statement_scope* scope) override;

	protected:
		virtual void parse_internal(Parser& parser) override;
	};
}
