
#pragma once

#include "SyntaxNode.h"
#include "Token.h"

class BinaryOperatorNode : public SyntaxNode
{
public:
	BinaryOperatorNode(Token* token);
};