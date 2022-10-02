
#pragma once

#include <vector>
#include "text_document.h"
#include "token.h"
#include "stmt/statement.h"
#include "typesystem/storage.h"
#include "lsp/diagnostic.h"

class source_project;

class translation_module
{
public:
	translation_module(source_project& project, std::string uri, Input_stream<utf16unit>& stream);
	~translation_module();

	void process();

	void tokenize();
	void parse_statements();
	void analyze_scope();
	void analyze_semantic();
	void compile();
	void compile_and_run();
	
	void clear();

	void print_statements();
	std::vector<lsp::diagnostic> get_diagnostics();

	token* get_token(lsp::position position);
	stmt::statement* get_statement(lsp::position position);

	source_project& project;

	std::string uri;
	Text_document document;
	std::vector<token*> tokens;
	std::vector<stmt::statement*> statements;

	statement_scope root_scope;

	typesystem::storage udt_storage;
};