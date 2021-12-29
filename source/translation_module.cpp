
#include "translation_module.h"

#include "Source_project.h"

Translation_module::Translation_module(Source_project& project, Input_stream<utf16unit>& stream)
	: project{ project }
	, document{ stream }
{
}

void Translation_module::process()
{
	Lexer lexer(document);
	Parser parser(lexer);
	parser.process();
}