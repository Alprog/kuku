
#pragma once

#include <vector>
#include <stmt/statement.h>

namespace typesystem
{
	struct builder
	{
		void build(std::vector<stmt::statement*> statements);
	};
};