
#include "symbol.h"

#include "symbol_table.h"

symbol::symbol(Symbol_table& symbol_table, Symbol_name name)
	: symbol_table{ symbol_table }
	, name{ name }
{
}