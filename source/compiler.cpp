
#include "stmt/all.h"
#include "ast/all.h"
#include "compiler.h"
#include "translation_module.h"
#include "err/statement_error.h"

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
		compile(statement);
	}
}

void compiler::start_new_function()
{

}

//---------------------------------------------------------------------------------------------------------------

template<typename T>
void compiler::compile(T& value)
{
	value->compile(*this);
}

template<>
void compiler::compile(ast::integer_literal& literal)
{
	spawn(instruction_PUSH_INT{ literal.value });
}

template<>
void compiler::compile(ast::string_literal& literal)
{
	// not implemented
}

template<>
void compiler::compile(ast::symbol_expression& expression)
{
	if (expression.reference.symbol != nullptr)
	{
		auto variable = dynamic_cast<variable_symbol*>(expression.reference.symbol);
		if (variable != nullptr)
		{
			spawn(instruction_GET_LOCAL{ (byte)variable->stack_offset });
		}
	}
}

template<>
void compiler::compile(ast::binary_operator_expression& expression)
{
	compile(expression.left);
	compile(expression.right);

	switch (expression.op.token_type)
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

		case token_type::Equal_operator:
			spawn(instruction_EQUAL{});
			break;

		case token_type::Not_equal_operator:
			spawn(instruction_NOT_EQUAL{});
			break;

		case token_type::Less_operator:
			spawn(instruction_LESS{});
			break;

		case token_type::Greater_operator:
			spawn(instruction_GREATER{});
			break;

		case token_type::Less_or_equal_operator:
			spawn(instruction_LESS{});
			break;

		case token_type::Greater_or_equal_operator:
			spawn(instruction_GREATER_OR_EQUAL{});
			break;

		default:
			throw std::exception("not implemented");
	}
}

template<>
void compiler::compile(stmt::variable_declaration_statement& statement)
{
	compile(statement.expression);

	auto variable_symbol = statement.get_symbol();
	variable_symbol->stack_offset = locals_size++;

	rt::localvar_info info;
	info.name = variable_symbol->name;
	info.stack_offset = variable_symbol->stack_offset;
	info.type_index = type_index::Integer;
	info.start_instruction = current_function->bytecode.bytes.size();
	info.end_instruction = -1;

	current_function->locals.push_back(info);
}

template<>
void compiler::compile(stmt::assign_statement& statement)
{
	compile(statement.rvalue);

	auto symbol_expression = dynamic_cast<ast::symbol_expression*>(statement.lvalue.get());
	if (symbol_expression)
	{
		auto symbol = symbol_expression->reference.symbol;
		byte local_offset = symbol->stack_offset;
		spawn(instruction_SET_LOCAL{ local_offset });
	}
}

template<>
void compiler::compile(stmt::expression_statement& statement)
{
	compile(statement.expression);
}

template<>
void compiler::compile(stmt::function_statement& statement)
{
	start_new_function();
}

template<>
void compiler::compile(stmt::end_statement& statement)
{
	int cutted_stack = 0;

	for (auto& local : current_function->locals)
	{
		if (local.end_instruction < 0 && local.stack_offset >= cutted_stack)
		{
			local.end_instruction = current_function->bytecode.bytes.size();
		}
	}

	//if (statement.get_scope()->statement->get_statement_type() == u"function_statement")
	//{

	//}
}
