
#include "scope_analyzer.h"
#include "stmt/scope.h"
#include "stmt/end_statement.h"

scope_analyzer::scope_analyzer(std::vector<stmt::statement*>& statements)
	: statements{ statements }
{
}

void scope_analyzer::analyze()
{
	stmt::scope scope;

	for (int i = 0; i < statements.size(); i++)
	{
		auto statement = statements[i];

		statement->sequence_number = i;
		statement->set_scope(scope);

		auto allowed_scope_types = statement->get_allowed_scopes();
		if ((allowed_scope_types & scope.get_type()) == stmt::scope_type::none)
		{
			statement->is_valid = false;
			statement->error_text = u"not valid scope";
			continue;
		}

		auto inner_scope_type = statement->get_inner_scope_type();
		if (inner_scope_type != stmt::scope_type::none)
		{
			scope = stmt::scope(statement);	
		}
		else if (dynamic_cast<stmt::end_statement*>(statement))
		{
			scope = scope.get_parent();
		}
	}
}