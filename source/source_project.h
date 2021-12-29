
#pragma once

#include <vector>
#include "translation_module.h"

class Source_project
{
public:
	void add_file(std::string uri);

private:
	std::vector<Translation_module*> modules;
};  