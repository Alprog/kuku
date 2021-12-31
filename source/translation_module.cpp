
#include "translation_module.h"

#include "source_project.h"
#include "console.h"

Translation_module::Translation_module(Source_project& project, Input_stream<utf16unit>& stream)
	: project{ project }
	, document{ stream }
{
}

void Translation_module::process()
{
    tokenize();
    parse_statements();
}

void Translation_module::tokenize()
{
	Lexer lexer(document);
    while (true)
    {
        auto token = lexer.get_next_token();
        tokens.push_back(token);
        if (token->type == Token_type::End_of_source)
        {
            break;
        }
    }
}

void Translation_module::parse_statements()
{
    Parser parser(project, &tokens[0]);
    while (true)
    {
        auto statement = parser.parse_next_statement();
        if (statement == nullptr) break;
        statements.push_back(statement);
    }
}

void Translation_module::print_statements()
{
    for (auto statement : statements)
    {
        auto line = statement->get_node_type() + u" " + (statement->is_valid ? u"1" : u"0");
        Console::write_line(line);

        if (!statement->is_valid)
        {
            Console::write_line(statement->error_text);
        }
    }
}

Token* Translation_module::get_token(Position position)
{
    for (auto token : tokens)
    {
        if (token->range.contains(position))
        {
            return token;
        }
    }
    return nullptr;
}