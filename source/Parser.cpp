
#include "parser.h"
#include "console.h"
#include "variable_node.h"
#include "binary_operator_node.h"
#include "variable_declaration_statement_node.h"
#include "assign_statement_node.h"
#include "invalid_statement_node.h"
#include "statement_node.h"
#include "end_statement_node.h"
#include "function_statement_node.h"
#include "class_statement_node.h"
#include "unexepected_error.h"

Parser::Parser(Token** it)
	: it{ it }
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

Token* startToken;

template <typename T>
T* Parser::create_node()
{
    auto node = new T();
    node->init(*this);
    return node;
}

Statement_node* Parser::parse_next_statement()
{
    skip_empty_tokens();
    if (current->type == Token_type::End_of_source)
    {
        return nullptr;
    }

    startToken = current;

    if (current->type == Token_type::Keyword)
    {
        if (current->get_source_text() == u"var")
        {
            return create_node<Variable_declaration_statement_node>();
        }
        else if (current->get_source_text() == u"end")
        {
            return create_node<End_statement_node>();
        }
        else if (current->get_source_text() == u"function")
        {
            return create_node<Function_statement_node>();
        }
        else if (current->get_source_text() == u"class")
        {
            return create_node<Class_statement_node>();
        }
    }
    else if (current->type == Token_type::Identifier)
    {
        auto id = current->get_source_text();
        next();
        if (current->type == Token_type::Assign_operator)
        {
            auto node = new Binary_operator_node(current);
            next();

            if (current->type == Token_type::Integer_literal)
            {
                next();
                if (current->type == Token_type::End_of_line)
                {
                    next();
                    return new Assign_statement_node();
                }
            }

        }
    }

    return (new Invalid_statement_node())->init(*this);
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

bool Parser::match_keyword(std::u16string keyword)
{
    if (current->type == Token_type::Keyword && current->get_source_text() == keyword)
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

void Parser::require_keyword(std::u16string keyword)
{
    if (!match_keyword(keyword))
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