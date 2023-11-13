#include "continue_statement.h"

#include "compiler.h"

void stmt::continue_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_continue);
}

void stmt::continue_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}