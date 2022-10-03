
#include "parser.h"
#include "console.h"
#include "ast/binary_operator_expression.h"
#include "ast/integer_literal.h"
#include "stmt/variable_declaration_statement.h"
#include "stmt/assign_statement.h"
#include "stmt/unknown_statement.h"
#include "stmt/statement.h"
#include "stmt/end_statement.h"
#include "stmt/function_statement.h"
#include "stmt/class_statement.h"
#include "unexepected_error.h"
#include "source_project.h"
#include "symbol_reference.h"
#include "stmt/expression_statement.h"
#include "stmt/return_statement.h"
#include "ast/string_literal.h"
#include "ast/symbol_expression.h"

Parser::Parser(translation_module& module, token** it)
	: module{ module }
	, it{ it }
	, current{ *it }
{
}

void Parser::skip_empty_tokens()
{
    while (current->type == Token_type::Comment || current->type == Token_type::End_of_line)
    {
        current = *(++it);
    }
}

void Parser::next()
{
    current = *(++it);
    while (current->type == Token_type::Comment)
    {
        current = *(++it);
    }
}

template <typename T>
T* Parser::create_statement(token* start_token)
{
	auto node = new T();
	node->init(*this, start_token ? start_token : current );
	return node;
}

template <typename T>
T* Parser::create_statement(token* start_token, std::unique_ptr<ast::expression> expression)
{
    auto node = new T( std::move( expression ) );
    node->init(*this, start_token);
    return node;
}

stmt::statement* Parser::parse_next_statement()
{
    skip_empty_tokens();
    if (current->type == Token_type::End_of_source)
    {
        return nullptr;
    }
    else if (current->type == Token_type::Keyword_var)
    {
        return create_statement<stmt::variable_declaration_statement>();
    }
    else if (current->type == Token_type::Keyword_end)
    {
        return create_statement<stmt::end_statement>();
    }
    else if (current->type == Token_type::Keyword_function)
    {
        return create_statement<stmt::function_statement>();
    }
    else if (current->type == Token_type::Keyword_class)
    {
        return create_statement<stmt::class_statement>();
    }
    else if (current->type == Token_type::Keyword_return)
    {
        return create_statement<stmt::return_statement>();
    }
    else
    {
        auto start_token = current;
        try
        {
            auto expression = parse_expression();
            if (current->type == Token_type::Assign_operator)
            {
                return create_statement<stmt::assign_statement>(start_token, std::move(expression));
            }
            else
            {
                return create_statement<stmt::expression_statement>(start_token, std::move(expression));
            }
        }
        catch (unexpected_error& error)
        {
            return create_statement<stmt::unknown_statement>(start_token);
        }
    }
}

std::unique_ptr<ast::expression> Parser::parse_expression()
{
    auto operand = parse_operand();

    binary_operator* binary_operator;
    while (match_binary_operator(precedence::maximum, binary_operator))
    {
        operand = parse_binary_operator_chain(std::move(operand), binary_operator);
    }

	return operand;
}

std::unique_ptr<ast::binary_operator_expression> Parser::parse_binary_operator_chain(std::unique_ptr<ast::expression> left_operand, binary_operator* current_operator)
{
    auto right_operand = parse_operand();

    auto precedence = current_operator->precedence;    
    binary_operator* next_operator;
    while (match_binary_operator(precedence, next_operator))
    {
        if (next_operator->precedence < precedence)
        {
            right_operand = parse_binary_operator_chain(std::move(right_operand), next_operator);
        }
        else if (next_operator->precedence == precedence)
        {
            left_operand = std::make_unique<ast::binary_operator_expression>(std::move(left_operand), *current_operator, std::move(right_operand));
            current_operator = next_operator;
            right_operand = parse_operand();
        }
    }

    return std::make_unique<ast::binary_operator_expression>(std::move(left_operand), *current_operator, std::move(right_operand));
}

std::unique_ptr<ast::expression> Parser::parse_operand()
{
    if (current->type == Token_type::Identifier)
    {
        auto symbol_expression = std::make_unique<ast::symbol_expression>(*current);
        next();
        return std::move(symbol_expression);
    }
    if (current->type == Token_type::Integer_literal)
    {
        auto literal = std::make_unique<ast::integer_literal>(*current);
        next();
        return std::move(literal);
    }
    if (current->type == Token_type::String_literal)
    {
        auto literal = std::make_unique<ast::string_literal>(*current);
        next();
        return std::move(literal);
    }
    if (current->type == Token_type::Open_parenthesis)
    {
        next();
        auto expression = parse_expression();
        require(Token_type::Close_parenthesis);
        return std::move(expression);
    }
    throw unexpected_error();
}

binary_operator* Parser::match_binary_operator(precedence maximum_precedence, binary_operator*& out_operator)
{
    for (auto& candidate : get_binary_operators())
    {
        if (candidate.token_type == current->type && candidate.precedence <= maximum_precedence)
        {
            out_operator = &candidate;
            next();
            return &candidate;
        }
    }
    return nullptr;
}

bool Parser::match(Token_type type)
{
    if (current->type == type)
    {
        next();
        return true;
    }
    return false;
}

bool Parser::match_end_of_statement()
{
    if (current->is_end_statement_token())
    {
        next();
        return true;
    }
    return false;
}

void Parser::require(Token_type type)
{
    if (!match(type))
    {
        throw unexpected_error();
    }
}

void Parser::require_end_of_statement()
{
    if (!match_end_of_statement())
    {
        throw unexpected_error();
    }
}

symbol_reference Parser::read_symbol_reference()
{
    if (current->type == Token_type::Identifier)
    {   
        auto name = current->get_source_text();
        auto reference = symbol_reference();
        reference.token = current;
        //current->symbol_reference = reference;
        next();
        return reference;
    }
    else
    {
        throw unexpected_error();
    }
    return {};
}