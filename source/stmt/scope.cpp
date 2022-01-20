
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