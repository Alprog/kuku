#pragma once

#include <vector>
#include "Lexer.h"
class StatementNode;

class Parser
{
public:
	Parser(Lexer& lexer);
	void process();

	Lexer& lexer;

	StatementNode* parseStatement();
	void parseExpression();

	Token current;
	
	bool match(TokenType type);
	bool matchKeyword(std::u16string keyword);
	bool matchEndOfStatement();

	void next(bool skipNewLines);
	std::vector<StatementNode*> statements;

	template <typename T>
	T* createNode();
};