#pragma once

#include <vector>
#include "Lexer.h"
#include "StatementNode.h"

class Parser
{
public:
	Parser(Lexer& lexer);
	void process();

private:
	Lexer& lexer;

	StatementNode* parseStatement();
	void parseExpression();

	Token current;
	
	void match(TokenType type);

	void next(bool skipNewLines);
	StatementNode* getInvalidToken();

	std::vector<StatementNode*> statements;
};