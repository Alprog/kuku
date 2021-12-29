
#pragma once

#include <string>
#include <vector>
#include "scope.h"
#include "token.h"

class Symbol_table;

using Symbol_name = std::u16string;

class Symbol
{
public:
	Symbol(Symbol_table& symbol_table, Symbol_name name);

	Symbol_table& symbol_table;
	Symbol_name name;

	//Scope& parent_scope;
	
	Token* definition_token;
	std::vector<Token*> usage_tokens;
};