
#pragma once

#include "syntax_node.h"
#include "class.h"
#include "token.h"
#include <vector>

class Variable_node : Syntax_node
{
public:
	std::u16string name;
	Class* type;

	Token* declaration_token;
};