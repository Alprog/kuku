
#pragma once

#include "statement.h"
#include "ast/expression.h"

namespace stmt
{
	class assign_statement : public stmt::statement
	{
	public:
		assign_statement(std::unique_ptr<ast::expression> expression);

		virtual std::u16string get_statement_type() const override { return u"assign_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }

		virtual void parse_internal(Parser& parser) override;

		std::unique_ptr<ast::expression> lvalue;
		std::unique_ptr<ast::expression> rvalue;
	};
}
