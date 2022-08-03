
#pragma once

#include "stmt/statement.h"
#include "symbol.h"
#include "symbol_reference.h"
#include "typesystem/info.h"

namespace stmt
{
	class symboled_statement_base : public virtual stmt::statement
	{
	public:
		symboled_statement_base(typesystem::info& info)
			: definition_symbol{ info, definition_reference }
		{
		}

		symbol definition_symbol;
		symbol_reference definition_reference;
	};

	template <typename InfoT>
	class symboled_statement : public symboled_statement_base
	{
	public:
		symboled_statement()
			: symboled_statement_base{ info }
		{
		}

		InfoT info;
	};
}