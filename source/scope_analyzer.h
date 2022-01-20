
#pragma once

#include <vector>
#include "stmt/statement.h"

class scope_analyzer
{
public:
	scope_analyzer(std::vector<stmt::statement*>& statements);
	void analyze();

private:
	std::vector<stmt::statement*>& statements;
};