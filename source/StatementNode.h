
#pragma once

#include "SyntaxNode.h"
#include "Token.h"

class StatementNode : SyntaxNode
{
public:
	Token* startToken;
	Token* endToken;
};