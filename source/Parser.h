#pragma once

#include <vector>
#include "lexer.h"
#include "statement_scope.h"

class symbol_reference;
class source_project;
namespace stmt
{
	class statement;
}

class Parser
{
public:
	Parser(source_project& project, token** it);
	void skip_empty_tokens();

	stmt::statement* parse_next_statement();
	void parse_expression();

	source_project& project;
	token** it;
	token* current;
	
	bool match(Token_type type);
	bool match_end_of_statement();

	void require(Token_type type);
	void require_end_of_statement();

	symbol_reference* read_symbol_reference();

	void next();
	std::vector<stmt::statement*> statements;

	template <typename T>
	T* create_node();
};