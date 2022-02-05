
#pragma once

#include "stmt/statement.h"
#include "statement_scope.h"

namespace stmt
{
	class scoped_statement : public statement
	{
	public:
		scoped_statement()
			: inner_scope(this)
		{
		}

	protected:
		statement_scope inner_scope;
	};
}