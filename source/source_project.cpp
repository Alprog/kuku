
#include "Source_project.h"
#include "unicode_streams.h"

void Source_project::add_file(std::string uri)
{
	Basic_input_stream basic_stream{ new std::basic_ifstream<utf8unit> { uri } };
	unicode::Utf8to16_stream u16stream(basic_stream);

	modules[uri] = new Translation_module(*this, u16stream);
}

void Source_project::add_file(std::string uri, std::u8string content)
{
	Basic_input_stream basic_stream{ new std::basic_istringstream{ content} };
	unicode::Utf8to16_stream u16stream{ basic_stream };

	modules[uri] = new Translation_module(*this, u16stream);
}

void Source_project::add_memory_snippet(std::u16string line)
{
	Basic_input_stream basic_stream{ new std::basic_istringstream{ line } };
	
	modules["memory"] = new Translation_module(*this, basic_stream);
}

void Source_project::process_all()
{
	for (auto& pair : modules)
	{
		pair.second->process();
	}
}

void Source_project::clear_all()
{
	for (auto& pair : modules)
	{
		delete pair.second;
	}
	modules.clear();
}

void Source_project::print_info()
{
	for (auto& pair : modules)
	{
		pair.second->print_statements();
	}
}

Translation_module* Source_project::get_module(std::string uri)
{
	auto it = modules.find(uri);
	if (it != std::end(modules))
	{
		return it->second;
	}
	return nullptr;
}