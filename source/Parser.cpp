
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

Parser::Parser(Lexer& lexer)
	: lexer{ lexer }
    , current{ nullptr }
{
}

void Parser::process()
{
    next(true);
    while (current->type != Token_type::End_of_source)
    {
        statements.push_back(parse_statement());
    }
}

void Parser::next(bool skip_new_lines)
{
    current = lexer.get_next_token();
    while (current->type == Token_type::Comment || (skip_new_lines && current->type == Token_type::End_of_line))
    {
        current = lexer.get_next_token();
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

Statement_node* Parser::parse_statement()
{
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
        Console::write_line(id);

        next(false);
        if (current->type == Token_type::Assign_operator)
        {
            auto node = new Binary_operator_node(current);
            next(false);

            if (current->type == Token_type::Integer_literal)
            {
                next(false);
                if (current->type == Token_type::End_of_line)
                {
                    next(false);
                    return new Assign_statement_node();
                }
            }

        }
    }

    return (new Invalid_statement_node())->init(*this);
}

void Parser::parse_expression()
{

}

bool Parser::require(Token_type type)
{
    if (!match(type))
    {
        throw Unexpected_error();
    }
}

bool Parser::match(Token_type type)
{
    if (current->type == type)
    {
        next(false);
        return true;
    }
    return false;
}

bool Parser::require_keyword(std::u16string keyword)
{
    if (!match_keyword(keyword))
    {
        throw Unexpected_error();
    }
}

bool Parser::match_keyword(std::u16string keyword)
{
    if (current->type == Token_type::Keyword && current->get_source_text() == keyword)
    {
        next(false);
        return true;
    }
    return false;
}

bool Parser::match_end_of_statement()
{
    if (current->is_end_statement_token())
    {
        next(false);
        return true;
    }
    return false;
}