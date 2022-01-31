
#include "statement_scope.h"
#include "stmt/statement.h"

statement_scope::statement_scope(stmt::statement* statement)
	: statement{ statement }
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

scope_type statement_scope::get_type()
{
	return is_root() ? scope_type::module_root : statement->get_inner_scope_type();
}