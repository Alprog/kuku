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
	
	
	bool match(Token_type type);
	bool match_keyword(std::u16string keyword);
	bool match_end_of_statement();

	void require(Token_type type);
	void require_keyword(std::u16string keyword);
	void require_end_of_statement();

	void next();
	std::vector<Statement_node*> statements;

	template <typename T>
	T* create_node();
};