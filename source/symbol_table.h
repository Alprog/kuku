
#pragma once

#include <map>
#include <string>

#include "symbol/symbol.h"
#include "symbol_record.h"

class symbol_table
{
public:
	short to_index(symbol* symbol);

private:
	std::vector<symbol_record> symbols;
	std::map<symbol*, short> indices;
};