
#pragma once

#include "SyntaxNode.h"
#include "Class.h"
#include "Token.h"
#include <vector>

class VariableNode : SyntaxNode
{
public:
	std::u16string name;
	Class* type;

	Token* declarationToken;
};