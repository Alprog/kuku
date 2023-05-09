
#include "compiler.h"
#include "translation_module.h"
#include "err/statement_error.h"
#include "stmt/scoped_statement.h"

compiler::compiler(translation_module& module)
	: module{ module }
{
}

void compiler::compile()
{
	module.root_scope.calculate_stack_offsets();

	for (auto& statement : module.statements)
	{
		if (!statement->is_valid)
		{
			throw statement_error(*statement);
		}

		auto scoped_statement = dynamic_cast<stmt::scoped_statement_base*>(statement);
		if (scoped_statement)
		{
			scoped_statement->inner_scope.calculate_stack_offsets();
		}
	}

	for (auto& statement : module.statements)
	{
		statement->compile(*this);
	}
}