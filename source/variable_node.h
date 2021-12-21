
#pragma once

#include "syntax_node.h"
#include "class.h"
#include "token.h"
#include <vector>

class VariableNode : SyntaxNode
{
public:
	std::u16string name;
	Class* type;

	Token* declarationToken;
};