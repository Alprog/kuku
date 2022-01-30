
#pragma once

#include <vector>
#include "scope_type.h"

class symbol;

namespace stmt
{
	class statement;
}

class scope
{
public:
	scope();
	scope(stmt::statement* statement);

	bool is_root();
	scope* get_parent();
	scope_type get_type();

	std::vector<symbol*> symbols;

	stmt::statement* statement;
};