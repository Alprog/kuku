
#include "symbol.h"

#include "symbol_table.h"

Symbol::Symbol(Symbol_table& symbol_table, Symbol_name name)
	: symbol_table{ symbol_table }
	, name{ name }
{
}