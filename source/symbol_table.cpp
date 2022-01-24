
#include "symbol_table.h"

symbol* Symbol_table::get_symbol(Symbol_name name)
{
	auto it = symbols.find(name);
	if (it != std::end(symbols))
	{
		return it->second;
	}
	else
	{
		auto new_symbol = new symbol(*this, name);
		symbols[name] = new_symbol;
		return new_symbol;
	}
}