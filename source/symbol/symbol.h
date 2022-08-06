
#pragma once

#include <string>
#include <vector>
#include "statement_scope.h"
#include "symbol_type.h"
#include "typesystem/info.h"

class symbol_reference;

using symbol_name = std::u16string;

class symbol
{
public:
	symbol(symbol_reference& definition);
	~symbol();

	symbol_name name;

	symbol_reference* definition;
	std::vector<symbol_reference*> usages;
};

