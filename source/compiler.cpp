
#include "compiler.h"
#include "translation_module.h"
#include "err/statement_error.h"

compiler::compiler(translation_module& module)
	: module{ module }
{
}

void compiler::compile()
{
	for (auto& statement : module.statements)
	{
		if (!statement->is_valid)
		{
			throw statement_error(*statement);
		}
	}

	for (auto& statement : module.statements)
	{
		statement->compile(*this);
	}
}