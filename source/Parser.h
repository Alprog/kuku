#pragma once

#include <vector>
#include "lexer.h"
#include "scope.h"

class Statement_node;

class Parser
{
public:
	Parser(Lexer& lexer);
	void process();

	Lexer& lexer;

	Statement_node* parse_statement();
	void parse_expression();

	Token* current;
	
	bool require(Token_type type);
	bool match(Token_type type);
	bool require_keyword(std::u16string keyword);
	bool match_keyword(std::u16string keyword);
	bool match_end_of_statement();

	void next(bool skip_new_lines);
	std::vector<Statement_node*> statements;

	template <typename T>
	T* create_node();


};