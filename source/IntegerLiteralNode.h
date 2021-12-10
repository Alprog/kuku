
#pragma once

#include "SingleTokenSyntaxNode.h"

class IntegerLiteralNode : SingleTokenSyntaxNode
{
public:
	IntegerLiteralNode(Token* token);

	int value;
};