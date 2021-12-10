
#pragma once

#include "SingleTokenSyntaxNode.h"

class BinaryOperatorNode : public SingleTokenSyntaxNode
{
public:
	BinaryOperatorNode(Token* token);
};