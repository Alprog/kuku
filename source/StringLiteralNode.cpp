
#include "StringLiteralNode.h"

StringLiteralNode::StringLiteralNode(Token* token)
{
	this->nodeToken = token;

	token->getSourceText();
}