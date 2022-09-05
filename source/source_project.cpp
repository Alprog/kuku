
#include "source_project.h"
#include "unicode_streams.h"

source_project::~source_project()
{
	clear_all();
}

void source_project::add_file(std::string uri)
{
	Basic_input_stream basic_stream{ new std::basic_ifstream<utf8unit> { uri } };
	unicode::Utf8to16_stream u16stream(basic_stream);

	modules[uri] = new translation_module(*this, u16stream);
}

void source_project::add_file(std::string uri, std::u8string content)
{
	Basic_input_stream basic_stream{ new std::basic_istringstream{ content} };
	unicode::Utf8to16_stream u16stream{ basic_stream };

	modules[uri] = new translation_module(*this, u16stream);
}

void source_project::add_memory_snippet(std::u16string line)
{
	Basic_input_stream basic_stream{ new std::basic_istringstream{ line } };
	
	modules["memory"] = new translation_module(*this, basic_stream);
}

void source_project::process_all()
{
	for (auto& pair : modules)
	{
		pair.second->process();
	}
}

void source_project::clear_all()
{
	for (auto& pair : modules)
	{
		delete pair.second;
	}
	modules.clear();
}

void source_project::print_info()
{
	for (auto& pair : modules)
	{
		pair.second->print_statements();
	}
}

translation_module* source_project::get_module(std::string uri)
{
	auto it = modules.find(uri);
	if (it != std::end(modules))
	{
		return it->second;
	}
	return nullptr;
}