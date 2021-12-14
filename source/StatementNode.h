
#pragma once

#include "SyntaxNode.h"
#include "Token.h"
#include "Parser.h"

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