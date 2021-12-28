
#pragma once

#include <string>
#include <vector>
#include "scope.h"
#include "token.h"

class Symbol
{
	Scope& parent_scope;
	std::u16string name;

	//Token definitionToken;
	std::vector<Token> usage_tokens;
};