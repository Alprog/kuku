
#pragma once

#include <vector>
#include "text_document.h"
#include "token.h"
#include "statement_node.h"

class Source_project;

class Translation_module
{
public:
	Translation_module(Source_project& project);

	Source_project& project;

	Text_document document;
	std::vector<Token*> tokens;
	std::vector<Statement_node*> statements;
};