
#include "symbol.h"

#include "symbol_table.h"

symbol::symbol(typesystem::info* info, symbol_reference* definition)
	: info { info }
	, definition { definition }
	, inner_scope { nullptr }
{

}

symbol::~symbol()
{

}