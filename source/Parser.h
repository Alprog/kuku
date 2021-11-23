#pragma once

#include "Lexer.h"

class Parser
{
public:
	Parser(Lexer& lexer);
	void process();

private:
	Lexer& lexer;

	Token getNextToken();
};