#include "if_statement.h"

#include "compiler.h"

void stmt::if_statement::parse_internal(parser& parser)
{
	parser.require(token_type::Keyword_if);
	condition = parser.parse_expression();
	parser.require(token_type::Keyword_then);
}

void stmt::if_statement::semantic_analyze()
{
	condition->semantic_analyze(*this);
}

void stmt::if_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}
