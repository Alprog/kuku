
#pragma once

#include "syntax_node.h"
#include "token.h"
#include "parser.h"

class StatementNode : SyntaxNode
{
public:
	Token* startToken;
	Token* endToken;

	bool IsValid;
	std::u16string errorText;

	StatementNode* init(Parser& parser);

	virtual int getNestingLevel();

protected:
	virtual bool parseInternal(Parser& parser) = 0;
};