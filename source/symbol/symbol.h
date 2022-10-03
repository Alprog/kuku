
#pragma once

#include <string>
#include <vector>
#include "statement_scope.h"
#include "symbol_type.h"
#include "typesystem/info.h"

class symbol_reference;

class symbol
{
public:
	symbol(symbol_reference& definition);
	~symbol();

	std::u16string name;

	symbol_reference* definition;
	std::vector<symbol_reference*> usages;
};
