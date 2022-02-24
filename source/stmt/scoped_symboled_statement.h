
#pragma once

#include "stmt/scoped_statement.h"
#include "stmt/symboled_statement.h"

namespace stmt
{
	template <scope_type ScopeType, typename InfoT>
	class scoped_symboled_statement : public stmt::scoped_statement<ScopeType>, public stmt::symboled_statement<InfoT>
	{
	public:
		scoped_symboled_statement()
		{
			symboled_statement<InfoT>::definition_symbol.inner_scope = &(scoped_statement<ScopeType>::inner_scope);
		}
	};
}