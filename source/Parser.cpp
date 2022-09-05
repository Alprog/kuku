
#include "parser.h"
#include "console.h"
#include "variable_node.h"
#include "binary_operator_node.h"
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
T* Parser::create_node()
{
    auto node = new T();
    node->init(*this);
    return node;
}

stmt::statement* Parser::parse_next_statement()
{
    skip_empty_tokens();
    if (current->type == Token_type::End_of_source)
    {
        return nullptr;
    }

    if (current->type == Token_type::Keyword_var)
    {
        return create_node<stmt::variable_declaration_statement>();
    }
    else if (current->type == Token_type::Keyword_end)
    {
        return create_node<stmt::end_statement>();
    }
    else if (current->type == Token_type::Keyword_function)
    {
        return create_node<stmt::function_statement>();
    }
    else if (current->type == Token_type::Keyword_class)
    {
        return create_node<stmt::class_statement>();
    }
    else if (current->type == Token_type::Identifier)
    {
        auto start_it = it;
        auto start_token = current;
        auto id = current->get_source_text();
        next();
        if (current->type == Token_type::Assign_operator)
        {
            next();

            if (current->type == Token_type::Integer_literal || current->type == Token_type::String_literal)
            {
                next();
                if (current->type == Token_type::End_of_line)
                {
                    auto statement = new stmt::assign_statement();
                    statement->start_token = start_token;
                    statement->end_token = current;
                    statement->is_valid = true;
                    next();
                    return statement;
                }
            }

        }
        current = start_token;
        it = start_it;
    }

    return (new stmt::unknown_statement())->init(*this);
}

void Parser::parse_expression()
{
    if (current->type == Token_type::Identifier)
    {
        next();

        while (true)
        {
            if (current->type == Token_type::Dot)
            {
                next();
                require(Token_type::Identifier);
            }
            else if (current->type == Token_type::Plus_sign)
            {
                next();
                parse_expression();
            }
            else
            {
                break;
            }
        }
    }
    else if (current->type == Token_type::Integer_literal)
    {
        next();
    }
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
        current->symbol_reference = reference;
        next();
        return reference;
    }
    else
    {
        throw unexpected_error();
    }
    return {};
}