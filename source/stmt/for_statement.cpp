#include "for_statement.h"

#include "compiler.h"

void stmt::for_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_for);
	// ??
}

void stmt::for_statement::semantic_analyze()
{
}

void stmt::for_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}
