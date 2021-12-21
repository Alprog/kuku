
#pragma once

#include "single_token_syntax_node.h"

class BinaryOperatorNode : public SingleTokenSyntaxNode
{
public:
	BinaryOperatorNode(Token* token);
};