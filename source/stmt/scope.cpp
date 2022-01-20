
#include "scope.h"
#include "statement.h"

stmt::scope::scope()
	: statement{ nullptr }
{
}

stmt::scope::scope(stmt::statement* statement)
	: statement{ statement }
{
}

bool stmt::scope::is_root()
{
	return statement == nullptr;
}

stmt::scope stmt::scope::get_parent()
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

stmt::scope_type stmt::scope::get_type()
{
	return is_root() ? stmt::scope_type::module_root : statement->get_inner_scope_type();
}