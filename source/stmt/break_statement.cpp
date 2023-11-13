#include "break_statement.h"

#include "compiler.h"

void stmt::break_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_break);
}

void stmt::break_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}