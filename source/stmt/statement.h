
#pragma once

#include "token.h"
#include "parser.h"

#define CHECK_END_OF_STATEMENT if (parser.current->is_end_statement_token()) return;

namespace stmt
{
	class statement
	{
	public:
		Token* start_token;
		Token* end_token;

		bool is_valid;
		std::u16string error_text;

		statement* init(Parser& parser);

		virtual int get_nesting_level();
		virtual std::u16string get_node_type() { return u"<unknown>"; }

	protected:
		virtual void parse_internal(Parser& parser) = 0;
	};
}
