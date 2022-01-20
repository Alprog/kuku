
#pragma once

#include "stmt/scope_type.h"

namespace stmt
{
	class statement;

	struct scope
	{
		scope();
		scope(stmt::statement* statement);

		bool is_root();
		stmt::scope get_parent();
		stmt::scope_type get_type();

		stmt::statement* statement;
	};
}