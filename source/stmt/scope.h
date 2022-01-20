
#pragma once

namespace stmt
{
	class statement;

	struct scope
	{
		scope();
		scope(stmt::statement* statement);

		bool is_root();
		scope get_parent();

		stmt::statement* statement;
	};
}