#pragma once

#include <vector>
#include "lexer.h"
#include "scope.h"

class Statement_node;

class Parser
{
public:
	Parser(Token** it);
	void skip_empty_tokens();

	Statement_node* parse_next_statement();
	void parse_expression();

	Token** it;
	Token* current;
	
	bool require(Token_type type);
	bool match(Token_type type);
	bool require_keyword(std::u16string keyword);
	bool match_keyword(std::u16string keyword);
	bool match_end_of_statement();

	void next();
	std::vector<Statement_node*> statements;

	template <typename T>
	T* create_node();


};