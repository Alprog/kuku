#pragma once

#include "Lexer.h"

class Parser
{
public:
	Parser(Lexer& lexer);
	void process();

private:
	Lexer& lexer;

	void parseStatement();
	void parseExpression();

	Token current;
	
	void match(TokenType type);

	void next(bool skipNewLines);
	void unexpected();
};