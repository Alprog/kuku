
#include "stmt/expression_statement.h"
#include "compiler.h"
#include "translation_module.h"
#include "err/statement_error.h"
#include "ast/integer_literal.h"
#include "ast/string_literal.h"
#include "stmt/scoped_statement.h"
#include "stmt/assign_statement.h"
#include "ast/symbol_expression.h"
#include "ast/expression.h"

compiler::compiler(translation_module& module)
	: module{ module }
{
	current_function = &chunk.functions.emplace_back();
	current_function->name = "main";
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

void compiler::start_new_function()
{

}

//---------------------------------------------------------------------------------------------------------------

template<>
void compiler::compile_impl(ast::integer_literal* literal)
{
	spawn(instruction_PUSH_INT{ literal->value });
}

template<>
void compiler::compile_impl(ast::string_literal* literal)
{
	// not implemented
}

template<>
void compiler::compile_impl(ast::symbol_expression* expression)
{
	if (expression->reference.symbol != nullptr)
	{
		auto variable = dynamic_cast<variable_symbol*>(expression->reference.symbol);
		if (variable != nullptr)
		{
			spawn(instruction_GET_LOCAL{ (byte)variable->stack_offset });
		}
	}
}

template<>
void compiler::compile_impl(ast::binary_operator_expression* expression)
{
	expression->left->compile(*this);
	expression->right->compile(*this);

	switch (expression->op.token_type)
	{
		case token_type::Plus_operator:
			spawn(instruction_INT_ADD{});
			break;

		case token_type::Minus_operator:
			spawn(instruction_INT_SUB{});
			break;

		case token_type::Multiply_Operator:
			spawn(instruction_INT_MULTIPLY{});
			break;

		case token_type::Divide_Operator:
			spawn(instruction_INT_DIVIDE{});
			break;

		case token_type::Exponent_operator:
			spawn(instruction_INT_POWER{});
			break;

		default:
			throw std::exception("not implemented");
	}
}

template<>
void compiler::compile_impl(stmt::assign_statement* statement)
{
	statement->rvalue->compile(*this);
}

template<>
void compiler::compile_impl(stmt::expression_statement* statement)
{
	statement->expression->compile(*this);
}