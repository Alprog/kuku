#pragma once

#include <vector>
#include "lexer.h"

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
	
	bool require(TokenType type);
	bool match(TokenType type);
	bool requireKeyword(std::u16string keyword);
	bool matchKeyword(std::u16string keyword);
	bool matchEndOfStatement();

	void next(bool skipNewLines);
	std::vector<StatementNode*> statements;

	template <typename T>
	T* createNode();
};