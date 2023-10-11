
#include "symbol_expression.h"
#include "symbol/variable_symbol.h"
#include "compiler.h"

ast::symbol_expression::symbol_expression(token& token)
{
	reference.token = &token;
}

void ast::symbol_expression::compile(compiler& compiler)
{
	if (reference.symbol != nullptr)
	{
		auto variable = dynamic_cast<variable_symbol*>(reference.symbol);
		if (variable != nullptr)
		{
			compiler.spawn(instruction_GET_LOCAL{ (byte)variable->stack_offset });
		}
	}
}

void ast::symbol_expression::semantic_analyze(stmt::statement& statement)
{
	reference.semantic_analyze(statement);
}