
#pragma once

#include "SingleTokenSyntaxNode.h"
#include "String.h"

class StringLiteralNode : public SingleTokenSyntaxNode
{
public:
	StringLiteralNode(Token* token);
};