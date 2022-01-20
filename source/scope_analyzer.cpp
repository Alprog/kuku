
#include "scope_analyzer.h"
#include "stmt/scope.h"

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

		auto level = statement->get_nesting_level();
		if (level != 0)
		{
			if (level > 0)
			{
				scope = stmt::scope(statement);
			}
			else
			{
				scope = scope.get_parent();
			}		
		}
	}
}