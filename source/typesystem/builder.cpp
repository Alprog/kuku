
#include "builder.h"
#include "typesystem/storage.h"

void typesystem::builder::build(std::vector<stmt::statement*> statements)
{
	auto storage = new typesystem::storage();

	for (auto statement : statements)
	{
		auto level = statement->get_nesting_level();
		if (level == 1)
		{
		}
	}
}