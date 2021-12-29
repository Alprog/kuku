
#include "Source_project.h"

void Source_project::add_file(std::string uri)
{
	auto module = new Translation_module(*this);
	modules.push_back(module);
}