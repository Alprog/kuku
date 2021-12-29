
#pragma once

#include <string>
#include <vector>
#include "scope.h"
#include "token.h"

using Symbol_name = std::u16string;

class Symbol
{
public:
	Symbol_name name;

	Scope& parent_scope;
	
	Token* definition_token;
	std::vector<Token*> usage_tokens;
};