
#include "symbol_table.h"

Symbol* Symbol_table::get_symbol(Symbol_name name)
{
	auto it = symbols.find(name);
	if (it != std::end(symbols))
	{
		return it->second;
	}
	else
	{
		auto symbol = new Symbol(*this, name);
		symbols[name] = symbol;
		return symbol;
	}
}