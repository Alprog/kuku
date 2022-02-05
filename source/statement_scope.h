
#pragma once

#include <vector>
#include "scope_type.h"

class symbol;

namespace stmt
{
	class statement;
}

class statement_scope
{
public:
	statement_scope(stmt::statement* statement);

	bool is_root();
	statement_scope* get_parent();
	scope_type get_type();

	void define_symbol(symbol* symbol);

	std::vector<symbol*> symbols;

	stmt::statement* statement;
};