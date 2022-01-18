
#pragma once

namespace stmt
{
	enum class statement_status
	{
		not_parsed,
		parsed,
		connected,
		semantic_validated
	};
}