
#include "statement_scope.h"
#include "stmt/statement.h"

statement_scope::statement_scope(stmt::statement* statement, scope_type type)
	: statement{ statement }
	, type{ type }
{
}

bool statement_scope::is_root()
{
	return statement == nullptr;
}

statement_scope* statement_scope::get_parent()
{
	if (is_root())
	{
		return this;
	}
	else
	{
		return statement->get_scope();
	}
}

void statement_scope::define_symbol(symbol* symbol)
{
	symbols.push_back(symbol);
}