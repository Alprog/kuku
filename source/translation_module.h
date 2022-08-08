
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
	~translation_module();

	void process();

	void tokenize();
	void parse_statements();
	void analyze_scope();
	void analyze_semantic();
	
	void clear();

	void print_statements();

	token* get_token(lsp::position position);

	source_project& project;

	Text_document document;
	std::vector<token*> tokens;
	std::vector<stmt::statement*> statements;

	typesystem::storage udt_storage;
};