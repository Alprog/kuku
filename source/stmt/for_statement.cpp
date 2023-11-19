#include "for_statement.h"

#include "compiler.h"

void stmt::for_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_for);
	parse_symbol(parser);
	parser.require(token_type::keyword_in);
	start_expression = parser.parse_expression();
	parser.require(token_type::double_dot);
	end_expression = parser.parse_expression();
	parser.require(token_type::keyword_do);
}

void stmt::for_statement::semantic_analyze()
{
}

void stmt::for_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}
