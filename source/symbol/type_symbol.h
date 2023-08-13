
#pragma once

#include <vector>
#include "symbol/symbol.h"
#include "symbol/field_symbol.h"
#include "symbol/function_symbol.h"

class type_symbol : public symbol
{
public:
	type_symbol* parent_type;

	std::vector<field_symbol*> fields;
	std::vector<function_symbol*> functions;
};