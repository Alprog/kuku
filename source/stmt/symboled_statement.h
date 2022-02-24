
#pragma once

#include "stmt/scoped_statement.h"
#include "symbol.h"
#include "symbol_reference.h"
#include "typesystem/info.h"

namespace stmt
{
	class symboled
	{
	public:
		symboled(typesystem::info* info)
			: definition_symbol{ info, &definition_reference }
		{
		}

		symbol definition_symbol;
		symbol_reference definition_reference;
	};

	class symboled_statement : public stmt::statement, public symboled
	{
	};

	class scoped_symboled_statement : public stmt::scoped_statement, public symboled
	{
	public:
		scoped_symboled_statement(typesystem::info* info )
			: symboled{ info }
		{
			definition_symbol.inner_scope = &inner_scope;
		}
	};
}