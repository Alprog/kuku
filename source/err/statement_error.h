
#pragma once

#include "error.h"
#include "stmt/statement.h"

class statement_error : public error
{
public:
	statement_error(stmt::statement& statement);

	virtual std::u16string get_message() override;

	stmt::statement& statement;
};