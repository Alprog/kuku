
#pragma once

#include <map>
#include <string>

#include "symbol.h"

class Symbol_table
{
public:
	symbol* get_symbol(symbol_name name);


private:
	std::map<symbol_name, symbol*> symbols;
};