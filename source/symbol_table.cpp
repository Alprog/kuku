
#include "symbol_table.h"

short symbol_table::to_index(symbol* symbol)
{
	auto it = indices.find(symbol);
	if (it != std::end(indices))
	{
		return it->second;
	}

	short index = symbols.size();
	symbols.push_back({ index, symbol->name, symbol });
	indices[symbol] = index;
	return index;
}