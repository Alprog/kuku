
#pragma once

#include "stmt/scoped_statement.h"
#include "symbol.h"
#include "symbol_reference.h"
#include "typesystem/info.h"

namespace stmt
{
	class symboled_statement : public stmt::scoped_statement
	{
	public:
		symboled_statement(typesystem::info* info )
			: definition_symbol{ info, &definition_reference }
		{
			definition_symbol.inner_scope = &inner_scope;
		}

		symbol definition_symbol;
		symbol_reference definition_reference;
	};
}