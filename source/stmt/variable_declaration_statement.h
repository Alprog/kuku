
#pragma once

#include "imperative_statement.h"
#include "parser.h"
#include "symboled_statement.h"
#include "typesystem/variable.h"

namespace stmt
{
	class variable_declaration_statement : public imperative_statement, public symboled
	{
	public:
		variable_declaration_statement();

		virtual std::u16string get_statement_type() override { return u"variable_declaration_statement"; }

		virtual void parse_internal(Parser& parser) override;

		symbol_reference* reference;

		typesystem::variable variable_info;

		virtual void define_symbols(statement_scope*& scope) override;
	};
}
