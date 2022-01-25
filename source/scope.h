
#pragma once

#include "scope_type.h"

namespace stmt
{
	class statement;
}

struct scope
{
	scope();
	scope(stmt::statement* statement);

	bool is_root();
	scope get_parent();
	scope_type get_type();

	stmt::statement* statement;
};