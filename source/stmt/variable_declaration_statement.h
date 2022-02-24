
#pragma once

#include "statement.h"
#include "parser.h"
#include "symboled_statement.h"
#include "typesystem/variable.h"

namespace stmt
{
	class variable_declaration_statement : public symboled_statement<typesystem::variable>
	{
	public:
		virtual std::u16string get_statement_type() override { return u"variable_declaration_statement"; }
		
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }

		virtual void parse_internal(Parser& parser) override;

		virtual void define_symbols(statement_scope* scope) override;
	};
}
