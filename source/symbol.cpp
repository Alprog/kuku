
#include "symbol.h"

#include "symbol_table.h"

symbol::symbol(symbol_name name)
	: name{ name }
	, definition{ nullptr }
{
}