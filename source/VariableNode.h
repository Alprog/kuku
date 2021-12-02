
#pragma once

#include "SyntaxNode.h"
#include "Class.h"
#include "Token.h"
#include <vector>

class VariableNode : SyntaxNode
{
	std::string name;
	Class* type;

	Token* declarationToken;
};