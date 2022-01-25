
#include "symbol_table.h"

symbol* Symbol_table::get_symbol(symbol_name name)
{
	auto it = symbols.find(name);
	if (it != std::end(symbols))
	{
		return it->second;
	}
	else
	{
		auto new_symbol = new symbol(name);
		symbols[name] = new_symbol;
		return new_symbol;
	}
}