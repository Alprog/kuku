
#pragma once

#include <vector>
#include "text_document.h"
#include "token.h"
#include "statement.h"

class Source_project;

class Translation_module
{
public:
	Translation_module(Source_project& project, Input_stream<utf16unit>& stream);

	void process();

	void tokenize();
	void parse_statements();
	void print_statements();

	Token* get_token(lsp::position position);

	Source_project& project;

	Text_document document;
	std::vector<Token*> tokens;
	std::vector<Statement*> statements;
};