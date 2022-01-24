
#pragma once

#include "symbol.h"
#include "token.h"

class symbol_reference
{
public:
	symbol_reference();

	token* token;
	symbol* symbol;
};