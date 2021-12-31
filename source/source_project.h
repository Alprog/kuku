
#pragma once

#include <map>
#include "translation_module.h"
#include "symbol_table.h"

class Source_project
{
public:
	void add_file(std::string uri);
	void add_file(std::string uri, std::basic_string<byte> content);
	void add_memory_snippet(std::u16string snippet);

	void process_all();
	void clear_all();

	void print_info();

	Translation_module* get_module(std::string uri);

	Symbol_table symbol_table;
private:
	std::map<std::string, Translation_module*> modules;
};  