
#include "parser.h"
#include "console.h"
#include "variable_node.h"
#include "binary_operator_node.h"
#include "variable_declaration_statement.h"
#include "assign_statement.h"
#include "unknown_statement.h"
#include "statement.h"
#include "end_statement.h"
#include "function_statement.h"
#include "class_statement.h"
#include "unexepected_error.h"
#include "source_project.h"

Parser::Parser(source_project& project, Token** it)
    : project{project}
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

Statement* Parser::parse_next_statement()
{
    skip_empty_tokens();
    if (current->type == Token_type::End_of_source)
    {
        return nullptr;
    }

    if (current->type == Token_type::Keyword_var)
    {
        return create_node<Variable_declaration_statement>();
    }
    else if (current->type == Token_type::Keyword_end)
    {
        return create_node<End_statement>();
    }
    else if (current->type == Token_type::Keyword_function)
    {
        return create_node<Function_statement>();
    }
    else if (current->type == Token_type::Keyword_class)
    {
        return create_node<Class_statement>();
    }
    else if (current->type == Token_type::Identifier)
    {
        auto id = current->get_source_text();
        next();
        if (current->type == Token_type::Assign_operator)
        {
            auto node = new Binary_operator_node(current);
            next();

            if (current->type == Token_type::Integer_literal || current->type == Token_type::String_literal)
            {
                next();
                if (current->type == Token_type::End_of_line)
                {
                    next();
                    auto statement = new Assign_statement();
                    statement->is_valid = true;
                    return statement;
                }
            }

        }
    }

    return (new Unknown_statement())->init(*this);
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
        throw Unexpected_error();
    }
}

void Parser::require_end_of_statement()
{
    if (!match_end_of_statement())
    {
        throw Unexpected_error();
    }
}

Symbol* Parser::read_symbol()
{
    if (current->type == Token_type::Identifier)
    {   
        auto name = current->get_source_text();
        auto symbol = project.symbol_table.get_symbol(name);
        symbol->usage_tokens.push_back(current);
        current->symbol = symbol;
        next();
        return symbol;
    }
    else
    {
        throw Unexpected_error();
    }
}