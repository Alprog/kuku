
#pragma once

#include "imperative_statement.h"
#include "parser.h"

namespace stmt
{
	class variable_declaration_statement : public imperative_statement
	{
		virtual std::u16string get_statement_type() override { return u"variable_declaration_statement"; }

	public:
		virtual void parse_internal(Parser& parser) override;

		symbol* symbol;
	};
}
