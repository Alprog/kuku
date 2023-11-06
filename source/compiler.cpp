
#include "stmt/all.h"
#include "ast/all.h"
#include "compiler.h"
#include "translation_module.h"
#include "err/statement_error.h"
#include "bytecode.h"
#include "instructions.h"

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

	spawn(instruction_END{});
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
		//spawn(instruction_POP{ pop_count });
	}
	for (auto& local : current_function->locals)
	{
		if (local.end_instruction < 0 && local.stack_offset >= new_stack_size)
		{
			local.end_instruction = current_function->bytecode.instructions.size();
		}
	}
}

void compiler::jump_here(int jump_place)
{
	int jump_offset = current_function->bytecode.instructions.size() - jump_place;
	reinterpret_cast<instruction_JUMP*>(&current_function->bytecode.instructions[jump_place])->A = jump_offset;
}

void compiler::spawn(base_instruction instruction)
{
	current_function->bytecode.instructions.push_back(instruction);
}

base_instruction& compiler::peek()
{
	auto& instructions = current_function->bytecode.instructions;
	return instructions[instructions.size() - 1];
}

base_instruction compiler::pop()
{
	base_instruction result = peek();
	current_function->bytecode.instructions.pop_back();
	return result;
}

opcode opeartor_token_to_opcode(token_type token_type)
{
	switch (token_type)
	{
		case token_type::Plus_operator:
			return opcode::ADD;

		case token_type::Less_operator:
			return opcode::L;

		case token_type::Minus_operator:
			return opcode::SUB;

		case token_type::Multiply_Operator:
			return opcode::MULTIPLY;

		case token_type::Divide_Operator:
			return opcode::DIVIDE;

		case token_type::Exponent_operator:
			return opcode::POWER;

		case token_type::Equal_operator:
			return opcode::EQ;

		case token_type::Not_equal_operator:
			return opcode::NEQ;

		case token_type::Greater_operator:
			return opcode::G;

		case token_type::Less_or_equal_operator:
			return opcode::LEQ;

		case token_type::Greater_or_equal_operator:
			return opcode::GEQ;

		default:
			throw std::exception("not implemented");
		}
}

inline_operand compiler::get_top_operand()
{
	inline_operand operand = { false, scope_context.locals_size - 1 };

	// forward value optimizations
	if (peek().A == operand.value)
	{
		if (peek().opcode == opcode::MOVE)
		{
			operand = inline_operand::from_RK_format(pop().B);
			scope_context.locals_size--;
		}
		else if (peek().opcode == opcode::CONSTANT)
		{
			operand = { true, pop().B };
			scope_context.locals_size--;
		}
	}

	return operand;
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
	const int index = current_function->add_constant(literal.value);
	spawn(instruction_CONSTANT{ (byte)scope_context.locals_size++, (byte)index });

	//spawn(instruction_SET_INT{ (byte)scope_context.locals_size++, (int16_t)literal.value });
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
			spawn(instruction_MOVE{ (byte)scope_context.locals_size, (byte)variable->stack_offset });
			scope_context.locals_size++;
		}
	}
}

template<>
void compiler::compile(ast::binary_operator_expression& expression)
{
	base_instruction instruction;
	instruction.opcode = opeartor_token_to_opcode(expression.op.token_type);

	instruction.A = (byte)scope_context.locals_size;

	compile(expression.left);
	instruction.B = get_top_operand().to_RK_format();

	compile(expression.right);
	instruction.C = get_top_operand().to_RK_format();

	spawn(instruction);

	scope_context.locals_size = instruction.A + 1;
}

template<>
void compiler::compile(stmt::variable_declaration_statement& statement)
{
	auto variable_symbol = statement.get_symbol();
	variable_symbol->stack_offset = scope_context.locals_size;

	rt::localvar_info info;
	info.name = variable_symbol->name;
	info.stack_offset = variable_symbol->stack_offset;
	info.type_index = type_index::Integer;
	info.start_instruction = current_function->bytecode.instructions.size();
	info.end_instruction = -1;

	compile(statement.expression);

	current_function->locals.push_back(info);
}

template<>
void compiler::compile(stmt::assign_statement& statement)
{
	auto symbol_expression = dynamic_cast<ast::symbol_expression*>(statement.lvalue.get());
	if (symbol_expression)
	{
		auto symbol = symbol_expression->reference.symbol;
		byte a = symbol->stack_offset;

		auto size = (byte)scope_context.locals_size;

		compile(statement.rvalue); // spawn src
		byte b = get_top_operand().to_RK_format();

		scope_context.locals_size = size;

		if (peek().opcode == opcode::ADD || peek().opcode == opcode::VALUE)
		{
			if (peek().A == scope_context.locals_size)
			{
				peek().A = a;
				return;
			}
		}
		
		spawn(instruction_MOVE{ a, b });
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
	auto size = scope_context.locals_size;

	compile(statement.condition);
	byte b = get_top_operand().to_RK_format();

	scope_context.skip_jump_place = current_function->bytecode.instructions.size();
	scope_context.locals_size = size;
	spawn(instruction_IFJUMP{ 0, b });
	
	enter_scope();
}

template<>
void compiler::compile(stmt::else_statement& statement)
{
	exit_scope();
	
	int tmp = current_function->bytecode.instructions.size();
	spawn(instruction_JUMP{ 0 });
	jump_here(scope_context.skip_jump_place);

	scope_context.skip_jump_place = tmp;

	enter_scope();
}

template<>
void compiler::compile(stmt::end_statement& statement)
{	
	exit_scope();
	jump_here(scope_context.skip_jump_place);
}

