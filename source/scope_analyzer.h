
#pragma once

#include <vector>
#include "stmt/statement.h"

class translation_module;

class scope_analyzer
{
public:
	scope_analyzer(translation_module& module, std::vector<stmt::statement*>& statements);
	void analyze();

private:
	translation_module& module;
	std::vector<stmt::statement*>& statements;
};