
#include "stmt/all.h"
#include "ast/all.h"
#include "compiler.h"
#include "translation_module.h"
#include "err/statement_error.h"
#include "bytecode.h"
#include "instructions.h"

bool optimizations = true;

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
	
	scope_contexts.push_emplace(0, 0, false);

	for (auto& statement : module.statements)
	{
		compile(statement);
	}

	spawn(instruction_END());
}

void compiler::start_new_function()
{

}

void compiler::enter_scope(bool is_loop)
{
	scope_contexts.push_emplace(get_current_place(), get_scope_context().stack_size, is_loop);
}

void compiler::enter_loop_scope()
{
	enter_scope(true);
}

void compiler::exit_scope()
{
	for (auto& jump_place : get_scope_context().jump_to_end_places)
	{
		int jump_offset = get_current_place() - jump_place;
		reinterpret_cast<instruction_JUMP*>(&current_function->bytecode.instructions[jump_place])->sBx = jump_offset;
	}

	scope_contexts.pop();

	int new_stack_size = scope_contexts.top().stack_size;
	for (auto& local : current_function->locals)
	{
		if (local.end_instruction < 0 && local.stack_offset >= new_stack_size)
		{
			local.end_instruction = get_current_place() - 1;
		}
	}
}

void compiler::define_local_variable(stmt::symboled_statement_base& statement)
{
	auto variable_symbol = statement.get_symbol();
	variable_symbol->stack_offset = get_scope_context().stack_size;

	rt::localvar_info info;
	info.name = variable_symbol->name;
	info.stack_offset = variable_symbol->stack_offset;
	info.type_index = type_index::Integer;
	info.start_instruction = get_current_place();
	info.end_instruction = -1;
	current_function->locals.push_back(info);
}

void compiler::spawn(base_instruction instruction)
{
	current_function->bytecode.instructions.push_back(instruction);
}

void compiler::spawn_jump_to_start()
{
	spawn_jump_to_start(get_scope_context());
}

void compiler::spawn_jump_to_start(scope_context& scope_context)
{
	int offset = scope_context.start_place - get_current_place();
	spawn(instruction_JUMP(offset));
}

void compiler::spawn_jump_to_end()
{
	spawn_jump_to_end(get_scope_context());
}

void compiler::spawn_jump_to_end(scope_context& scope_context)
{
	scope_context.jump_to_end_places.push_back(get_current_place());
	spawn(instruction_JUMP(0));
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
		case token_type::plus_operator:
			return opcode::ADD;

		case token_type::less_operator:
			return opcode::L;

		case token_type::minus_operator:
			return opcode::SUB;

		case token_type::multiply_Operator:
			return opcode::MULT;

		case token_type::divide_Operator:
			return opcode::DIVIDE;

		case token_type::exponent_operator:
			return opcode::POWER;

		case token_type::equal_operator:
			return opcode::EQ;

		case token_type::not_equal_operator:
			return opcode::NEQ;

		case token_type::greater_operator:
			return opcode::G;

		case token_type::less_or_equal_operator:
			return opcode::LEQ;

		case token_type::greater_or_equal_operator:
			return opcode::GEQ;

		default:
			throw std::exception("not implemented");
		}
}

inline_operand compiler::get_top_operand()
{
	inline_operand operand = { instruction_mode::R, scope_contexts.top().stack_size - 1};

	// forward value optimizations
	if (optimizations)
	{
		if (peek().A == operand.value)
		{
			auto opcode = peek().opcode;
			if (opcode == opcode::ASSIGN || opcode == opcode::ASSIGN_K)
			{
				operand = { peek().MB, pop().B };
				get_scope_context().stack_size--;
			}
		}
	}

	return operand;
}

int compiler::get_current_place()
{
	return current_function->bytecode.instructions.size();
}

scope_context& compiler::get_loop_context(int level)
{
	auto& elements = scope_contexts.elements;
	for (int i = elements.size() - 1; i >= 0; i--)
	{
		if (elements[i].is_loop)
		{
			if (--level == 0)
			{
				return elements[i];
			}
		}
	}
	throw std::exception("can't find loop context");
}

scope_context& compiler::get_scope_context()
{
	return scope_contexts.top(); 
}

//---------------------------------------------------------------------------------------------------------------

bool has_regA(opcode code)
{
	switch (code)
	{
		case opcode::ADD:
		case opcode::ADD_RK:
		case opcode::ADD_KR:
		case opcode::ADD_KK:
		case opcode::SUB:
		case opcode::SUB_RK:
		case opcode::SUB_KR:
		case opcode::SUB_KK:
		case opcode::MULT:
		case opcode::MULT_RK:
		case opcode::MULT_KR:
		case opcode::MULT_KK:
		case opcode::DIVIDE:
		case opcode::DIVIDE_RK:
		case opcode::DIVIDE_KR:
		case opcode::DIVIDE_KK:
		case opcode::POWER:
		case opcode::POWER_RK:
		case opcode::POWER_KR:
		case opcode::POWER_KK:
		case opcode::EQ:
		case opcode::EQ_RK:
		case opcode::EQ_KR:
		case opcode::EQ_KK:
		case opcode::NEQ:
		case opcode::NEQ_RK:
		case opcode::NEQ_KR:
		case opcode::NEQ_KK:
		case opcode::L:
		case opcode::L_RK:
		case opcode::L_KR:
		case opcode::L_KK:
		case opcode::G:
		case opcode::G_RK:
		case opcode::G_KR:
		case opcode::G_KK:
		case opcode::LEQ:
		case opcode::LEQ_RK:
		case opcode::LEQ_KR:
		case opcode::LEQ_KK:
		case opcode::GEQ:
		case opcode::GEQ_RK:
		case opcode::GEQ_KR:
		case opcode::GEQ_KK:
		case opcode::ASSIGN:
		case opcode::ASSIGN_K:
		case opcode::VALUE:
			return true;
	}

	return false;
}

template<typename T>
void compiler::compile(T& value)
{
	value->compile(*this);
}

template<>
void compiler::compile(ast::integer_literal& literal)
{
	const int index = current_function->add_constant(literal.value);
	spawn(instruction_ASSIGN(instruction_mode::K, get_scope_context().stack_size++, index));
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
			spawn(instruction_ASSIGN(instruction_mode::R, get_scope_context().stack_size, variable->stack_offset));
			get_scope_context().stack_size++;
		}
	}
}

template<>
void compiler::compile(ast::binary_operator_expression& expression)
{
	base_instruction instruction;
	instruction.opcode = opeartor_token_to_opcode(expression.op.token_type);

	instruction.A = (byte)get_scope_context().stack_size;

	compile(expression.left);
	instruction.set_B_cell(get_top_operand());

	compile(expression.right);
	instruction.set_C_cell(get_top_operand());

	spawn(instruction);

	get_scope_context().stack_size = instruction.A + 1;
}

template<>
void compiler::compile(stmt::variable_declaration_statement& statement)
{
	define_local_variable(statement);
	compile(statement.expression);
}

template<>
void compiler::compile(stmt::assign_statement& statement)
{
	auto symbol_expression = dynamic_cast<ast::symbol_expression*>(statement.lvalue.get());
	if (symbol_expression)
	{
		auto symbol = symbol_expression->reference.symbol;
		byte a = symbol->stack_offset;

		auto size = (byte)get_scope_context().stack_size;

		compile(statement.rvalue); // spawn src
		inline_operand b = get_top_operand();
		get_scope_context().stack_size = size;

		// last command retarget optimization 
		if (optimizations)
		{
			if (has_regA(peek().opcode))
			{
				if (peek().A == get_scope_context().stack_size)
				{
					peek().A = a;
					return;
				}
			}
		}

		spawn(instruction_ASSIGN(b.mode, a, b.value));
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
	enter_scope();

	auto size = get_scope_context().stack_size;

	compile(statement.condition);
	inline_operand b = get_top_operand();

	if (b.mode == instruction_mode::R)
	{
		get_scope_context().jump_to_end_places.push_back(get_current_place());
		spawn(instruction_IFJUMP(b.value, 0));
	}
	else
	{
		if (!current_function->constant_buffer[b.value].boolean)
		{
			spawn_jump_to_end();
		}
	}
	
	get_scope_context().stack_size = size;
}

template<>
void compiler::compile(stmt::else_statement& statement)
{
	int jump_place = get_current_place();
	spawn(instruction_JUMP(0));

	exit_scope();
	enter_scope(false);

	get_scope_context().jump_to_end_places.push_back(jump_place);
}

template<>
void compiler::compile(stmt::end_statement& statement)
{	
	exit_scope();
}

template<>
void compiler::compile(stmt::while_statement& statement)
{
	enter_scope(true);

	auto size = get_scope_context().stack_size;

	compile(statement.condition);
	inline_operand b = get_top_operand();

	if (b.mode == instruction_mode::R)
	{
		get_scope_context().jump_to_end_places.push_back(get_current_place());
		spawn(instruction_IFJUMP(b.value, 0));
	}
	else
	{
		if (!current_function->constant_buffer[b.value].boolean)
		{
			spawn_jump_to_end();
		}
	}

	get_scope_context().stack_size = size;
}

template<>
void compiler::compile(stmt::for_statement& statement)
{
	enter_scope();

	uint8_t index = (uint8_t)get_scope_context().stack_size;

	// index + 0: counter
	// index + 1: max_value
	// index + 2: temp comparison

	// preparation
	define_local_variable(statement);
	compile(statement.start_expression);
	compile(statement.end_expression);
	spawn(instruction_JUMP(2));

	get_scope_context().start_place = get_current_place();

	// increment
	spawn(instruction_INC(index));

	// condition
	spawn(instruction_LEQ(instruction_mode::RR, index + 2, index, index + 1));
	get_scope_context().jump_to_end_places.push_back(get_current_place());
	spawn(instruction_IFJUMP(index + 2, 0));
}

template<>
void compiler::compile(stmt::loop_statement& statement)
{
	spawn_jump_to_start();
	exit_scope();
}

template<>
void compiler::compile(stmt::continue_statement& statement)
{
	spawn_jump_to_start(get_loop_context(statement.level));
}

template<>
void compiler::compile(stmt::break_statement& statement)
{
	spawn_jump_to_end(get_loop_context(statement.level));
}

