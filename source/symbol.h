
#pragma once

#include <string>
#include <vector>
#include "scope.h"
#include "token.h"

class Symbol_table;

using Symbol_name = std::u16string;

class symbol
{
public:
	symbol(Symbol_table& symbol_table, Symbol_name name);

	Symbol_table& symbol_table;
	Symbol_name name;

	//Scope& parent_scope;
	
	token* definition_token;
	std::vector<token*> usage_tokens;
};