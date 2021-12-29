
#pragma once

#include <map>
#include <string>

#include "symbol.h"

class Symbol_table
{
public:
	Symbol* get_symbol(Symbol_name name);


private:
	std::map<Symbol_name, Symbol*> symbols;
};