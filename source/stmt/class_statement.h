
#pragma once

#include "statement.h"
#include "symbol.h"
#include "typesystem/type.h"

namespace stmt
{
	class class_statement : public statement
	{
	public:
		class_statement();

		virtual std::u16string get_statement_type() override { return u"class_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::module_root; }
		virtual scope_type get_inner_scope_type() const override { return scope_type::class_body; }

	protected:
		virtual void parse_internal(Parser& parser) override;
		virtual void define_symbols(statement_scope*& scope) override;

		symbol_reference* definition;

		typesystem::type* type_info;
		statement_scope scope;
	};
}
