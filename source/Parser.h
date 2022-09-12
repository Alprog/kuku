#pragma once

#include <vector>
#include "lexer.h"
#include "statement_scope.h"

class symbol_reference;
class translation_module;
namespace stmt
{
	class statement;
}

class Parser
{
public:
	Parser(translation_module& module, token** it);
	void skip_empty_tokens();

	stmt::statement* parse_next_statement();
	void parse_operand();
	void parse_expression();

	translation_module& module;
	token** it;
	token* current;
	
	bool match(Token_type type);
	bool match_end_of_statement();

	void require(Token_type type);
	void require_end_of_statement();

	symbol_reference read_symbol_reference();

	void next();
	std::vector<stmt::statement*> statements;

	template <typename T>
	T* create_node();
};