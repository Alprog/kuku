
#pragma once

#include "symbol/symbol.h"
#include "token.h"

class symbol_reference
{
public:
	symbol_reference();

	token* token;
	symbol* symbol;
};