
#pragma once

#include <vector>
#include "text_document.h"
#include "token.h"
#include "stmt/statement.h"
#include "typesystem/storage.h"

class source_project;

class translation_module
{
public:
	translation_module(source_project& project, Input_stream<utf16unit>& stream);

	void process();

	void tokenize();
	void parse_statements();
	void print_statements();

	Token* get_token(lsp::position position);

	source_project& project;

	Text_document document;
	std::vector<Token*> tokens;
	std::vector<stmt::statement*> statements;

	typesystem::storage udt_storage;
};