
#pragma once

#include <vector>
#include "translation_module.h"
#include "symbol_table.h"

class Source_project
{
public:
	void add_file(std::string uri);
	void add_memory_snippet(std::u16string snippet);

	void process_all();
	void clear_all();

	Symbol_table symbol_table;
private:
	std::vector<Translation_module*> modules;
};  