
#include "translation_module.h"

#include "source_project.h"
#include "console.h"

translation_module::translation_module(source_project& project, Input_stream<utf16unit>& stream)
	: project{ project }
	, document{ stream }
{
}

void translation_module::process()
{
    tokenize();
    parse_statements();
}

void translation_module::tokenize()
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

void translation_module::parse_statements()
{
    Parser parser(project, &tokens[0]);
    while (true)
    {
        auto statement = parser.parse_next_statement();
        if (statement == nullptr) break;
        statements.push_back(statement);
    }
}

void translation_module::print_statements()
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

Token* translation_module::get_token(lsp::position position)
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