
#include "scope_analyzer.h"
#include "statement_scope.h"
#include "stmt/scoped_statement.h"
#include "stmt/symboled_statement.h"
#include "stmt/end_statement.h"
#include "translation_module.h"
#include "source_project.h"

scope_analyzer::scope_analyzer(translation_module& module, std::vector<stmt::statement*>& statements)
	: module{ module }
	, statements{ statements }
{
}

void scope_analyzer::analyze()
{
	auto current_scope = &module.root_scope;
	
	for (int i = 0; i < statements.size(); i++)
	{
		auto statement = statements[i];

		statement->sequence_number = i;
		statement->set_scope(current_scope);

		auto allowed_scope_types = statement->get_allowed_scopes();
		if ((allowed_scope_types & current_scope->type) == scope_type::none)
		{
			statement->is_valid = false;
			statement->error_text = u"not valid scope";
			continue;
		}

		auto symboled_statement = dynamic_cast<stmt::symboled_statement_base*>(statement);
		if (symboled_statement)
		{
			current_scope->define_symbol(symboled_statement->get_symbol());
		}
		
		auto scoped_statement = dynamic_cast<stmt::scoped_statement_base*>(statement);
		if (scoped_statement)
		{
			current_scope = &scoped_statement->inner_scope;
		}
		else if (dynamic_cast<stmt::end_statement*>(statement))
		{
			current_scope = current_scope->get_parent();
		}
	}
}