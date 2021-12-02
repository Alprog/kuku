
#pragma once

#include "SyntaxNode.h"
#include "String.h"

class StringLiteralNode : public SyntaxNode
{
public:
	StringLiteralNode(Token* token);
};