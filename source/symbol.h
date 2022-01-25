
#pragma once

#include <string>
#include <vector>
#include "scope.h"

class symbol_reference;

using symbol_name = std::u16string;

class symbol
{
public:
	symbol(symbol_name name);

	symbol_name name;

	//Scope& parent_scope;
	
	symbol_reference* definition;
	std::vector<symbol_reference*> usages;
};