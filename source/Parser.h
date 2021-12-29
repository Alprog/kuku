#pragma once

#include <vector>
#include "lexer.h"
#include "scope.h"

class Statement;
class Symbol;
class Source_project;

class Parser
{
public:
	Parser(Source_project& project, Token** it);
	void skip_empty_tokens();

	Statement* parse_next_statement();
	void parse_expression();

	Source_project& project;
	Token** it;
	Token* current;
	
	bool match(Token_type type);
	bool match_end_of_statement();

	void require(Token_type type);
	void require_end_of_statement();

	Symbol* read_symbol();

	void next();
	std::vector<Statement*> statements;

	template <typename T>
	T* create_node();
};