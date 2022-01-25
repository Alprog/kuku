
#include "scope.h"
#include "stmt/statement.h"

scope::scope()
	: statement{ nullptr }
{
}

scope::scope(stmt::statement* statement)
	: statement{ statement }
{
}

bool scope::is_root()
{
	return statement == nullptr;
}

scope scope::get_parent()
{
	if (is_root())
	{
		return *this;
	}
	else
	{
		return statement->get_scope();
	}
}

scope_type scope::get_type()
{
	return is_root() ? scope_type::module_root : statement->get_inner_scope_type();
}