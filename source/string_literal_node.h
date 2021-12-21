
#pragma once

#include "single_token_syntax_node.h"
#include "string.h"

class StringLiteralNode : public SingleTokenSyntaxNode
{
public:
	StringLiteralNode(Token* token);
};