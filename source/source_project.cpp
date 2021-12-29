
#include "Source_project.h"
#include "unicode_streams.h"

void Source_project::add_file(std::string uri)
{
	std::basic_ifstream<byte> file_stream(uri);
	Basic_input_stream basic_stream(file_stream);
	unicode::Utf8to16_stream u16stream(basic_stream);

	auto module = new Translation_module(*this, u16stream);
	modules.push_back(module);
}

void Source_project::add_memory_snippet(std::u16string line)
{
	std::basic_istringstream string_stream{ line };
	Basic_input_stream basic_stream{ string_stream };
	
	auto module = new Translation_module(*this, basic_stream);
	modules.push_back(module);
}

void Source_project::process_all()
{
	for (auto& module : modules)
	{
		module->process();
	}
}

void Source_project::clear_all()
{
	for (auto& module : modules)
	{
		delete module;
	}
	modules.clear();
}

void Source_project::print_info()
{
	for (auto& module : modules)
	{
		module->print_statements();
	}
}