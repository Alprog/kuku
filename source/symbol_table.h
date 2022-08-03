
#pragma once

#include <map>
#include <string>

#include "symbol.h"

class symbol_table
{
public:
	void register_symbol(symbol& symbol);
	void remove_symbol(symbol& symbol);

	symbol* get_symbol(symbol_name name);

private:
	std::map<symbol_name, symbol*> symbols;
};