
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
	for (auto& statement : module.statements)
	{
		if (!statement->is_valid)
		{
			throw statement_error(*statement);
		}
	}

	scope_context.locals_size = 0;
	scope_context.skip_jump_place = 0;

	enter_scope();
	for (auto& statement : module.statements)
	{
		compile(statement);
	}
}

void compiler::start_new_function()
{

}

void compiler::enter_scope()
{
	scope_context.push_state();
}

void compiler::exit_scope()
{
	int old_stack_size = scope_context.locals_size;
	scope_context.pop_state();

	int new_stack_size = scope_context.locals_size;
	byte pop_count = (byte)(old_stack_size - new_stack_size);
	if (pop_count > 0)
	{
		spawn(instruction_POP{ pop_count });
	}
	for (auto& local : current_function->locals)
	{
		if (local.end_instruction < 0 && local.stack_offset >= new_stack_size)
		{
			local.end_instruction = current_function->bytecode.bytes.size();
		}
	}
}

void compiler::jump_here(int jump_place)
{
	int jump_offset = current_function->bytecode.bytes.size() - jump_place;
	reinterpret_cast<instruction_JUMP*>(&current_function->bytecode.bytes[jump_place])->jump_offset = jump_offset;
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
	variable_symbol->stack_offset = scope_context.locals_size++;

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
void compiler::compile(stmt::if_statement& statement)
{
	compile(statement.condition);

	enter_scope();

	scope_context.skip_jump_place = current_function->bytecode.bytes.size();
	spawn(instruction_JUMP_ON_FALSE{ 0 });
}

template<>
void compiler::compile(stmt::else_statement& statement)
{
	int jump_place = scope_context.skip_jump_place;

	exit_scope();

	int temp = current_function->bytecode.bytes.size();
	spawn(instruction_JUMP{ 0 });
	jump_here(jump_place);

	enter_scope();	

	scope_context.skip_jump_place = temp;
}

template<>
void compiler::compile(stmt::end_statement& statement)
{	
	int jump_place = scope_context.skip_jump_place;
	exit_scope();
	jump_here(jump_place);
}

