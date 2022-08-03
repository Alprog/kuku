
#include "symbol_table.h"

void symbol_table::register_symbol(symbol& symbol)
{
	symbols[symbol.name] = &symbol;
}

void symbol_table::remove_symbol(symbol& symbol)
{
	symbols.erase(symbol.name);
}

symbol* symbol_table::get_symbol(symbol_name name)
{
	return nullptr;
}