
#pragma once

#include "single_token_syntax_node.h"

class IntegerLiteralNode : SingleTokenSyntaxNode
{
public:
	IntegerLiteralNode(Token* token);

	int value;
};