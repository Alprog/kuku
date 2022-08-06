
#pragma once

#include "stmt/statement.h"
#include "symbol/symbol.h"
#include "symbol_reference.h"
#include "typesystem/info.h"
#include <type_traits>
#include "parser.h"

namespace stmt
{
	class symboled_statement_base : public virtual stmt::statement
	{
	public:
		virtual symbol* get_symbol() = 0;

		symbol_reference symbol_definition_reference;
	};

	template <typename T>
	concept symbol_type = std::is_base_of<symbol, T>::value;

	template <symbol_type SymbolT>
	class symboled_statement : public symboled_statement_base
	{
	public:
		virtual symbol* get_symbol() override { return symbol; }

		void parse_symbol(Parser& parser)
		{
			symbol_definition_reference = *parser.read_symbol_reference();
			symbol = new SymbolT(symbol_definition_reference);
			symbol_definition_reference.symbol = symbol;
		}

		SymbolT* symbol;
	};
}