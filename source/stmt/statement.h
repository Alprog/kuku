
#pragma once

#include "token.h"
#include "parser.h"
#include "statement_scope.h"
#include "scope_type.h"

#define CHECK_END_OF_STATEMENT if (parser.current->is_end_statement_token()) return;

namespace stmt
{
	class statement
	{
	public:
		token* start_token;
		token* end_token;

		int sequence_number;

		bool is_valid;
		std::u16string error_text;

		statement* init(Parser& parser);

		virtual scope_type get_allowed_scopes() const = 0;

		virtual std::u16string get_statement_type() { return u"<unknown>"; }

		statement_scope* get_scope();
		void set_scope(statement_scope* scope);

		virtual void define_symbols(statement_scope* scope);

	protected:
		virtual void parse_internal(Parser& parser) = 0;

		statement_scope* scope;
	};
}
