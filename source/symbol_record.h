
#pragma once

#include <map>
#include <string>

#include "symbol/symbol.h"

struct symbol_record
{
	int index;
	std::u16string name;
	symbol* symbol;
};