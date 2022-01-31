
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
	symbol(typesystem::info* info, symbol_reference* definition);

	typesystem::info* info;

	symbol_name name;

	//Scope& parent_scope;
	
	symbol_reference* definition;
	std::vector<symbol_reference*> usages;
	statement_scope* inner_scope;
};