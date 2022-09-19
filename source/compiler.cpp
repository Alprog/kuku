
#include "compiler.h"
#include "translation_module.h"

compiler::compiler(translation_module& module)
	: module{ module }
{
}

void compiler::compile()
{
	for (auto& statement : module.statements)
	{
		statement->compile(*this);
	}
}