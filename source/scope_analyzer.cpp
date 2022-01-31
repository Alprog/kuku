
#include "scope_analyzer.h"
#include "statement_scope.h"
#include "stmt/end_statement.h"

scope_analyzer::scope_analyzer(std::vector<stmt::statement*>& statements)
	: statements{ statements }
{
}

void scope_analyzer::analyze()
{
	auto current_scope = new statement_scope();
	
	for (int i = 0; i < statements.size(); i++)
	{
		auto statement = statements[i];

		statement->sequence_number = i;
		statement->set_scope(current_scope);

		auto allowed_scope_types = statement->get_allowed_scopes();
		if ((allowed_scope_types & current_scope->get_type()) == scope_type::none)
		{
			statement->is_valid = false;
			statement->error_text = u"not valid scope";
			continue;
		}

		statement->define_symbols(current_scope);

		auto inner_scope_type = statement->get_inner_scope_type();
		if (inner_scope_type != scope_type::none)
		{
			current_scope = new statement_scope(statement);
		}
		else if (dynamic_cast<stmt::end_statement*>(statement))
		{
			current_scope = current_scope->get_parent();
		}
	}
}