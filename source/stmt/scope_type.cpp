
#include "scope_type.h"

stmt::scope_type stmt::operator|(stmt::scope_type lhs, stmt::scope_type rhs)
{
	return static_cast<stmt::scope_type>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

stmt::scope_type stmt::operator&(stmt::scope_type lhs, stmt::scope_type rhs)
{
	return static_cast<stmt::scope_type>(static_cast<int>(lhs) & static_cast<int>(rhs));
}