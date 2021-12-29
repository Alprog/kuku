
#pragma once

#include <map>
#include <string>

#include "symbol.h"

class Symbol_table
{
	std::map<Symbol_name, Symbol> symbols;
};