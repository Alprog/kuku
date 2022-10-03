
#pragma once

#include <map>
#include <string>

#include "symbol/symbol.h"

class symbol_table
{
public:
	void register_symbol(symbol& symbol);
	void remove_symbol(symbol& symbol);

	symbol* get_symbol(std::u16string name);

private:
	std::map<std::u16string, symbol*> symbols;
};