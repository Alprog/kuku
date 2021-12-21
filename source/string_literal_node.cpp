
#include "string_literal_node.h"

StringLiteralNode::StringLiteralNode(Token* token)
{
	this->nodeToken = token;

	token->getSourceText();
}