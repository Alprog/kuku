
#pragma once

#include <string>
#include <vector>
#include "scope.h"
#include "token.h"

class Symbol
{
	Scope& parentScope;
	std::u16string name;

	//Token definitionToken;
	std::vector<Token> usageTokens;

};