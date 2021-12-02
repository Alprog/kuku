
#pragma once

#include "SyntaxNode.h"

class IntegerLiteralNode : SyntaxNode
{
public:
	IntegerLiteralNode(Token* token);

	int value;
};