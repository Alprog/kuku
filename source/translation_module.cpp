
#include "translation_module.h"

#include "Source_project.h"

Translation_module::Translation_module(Source_project& project, Input_stream<utf16unit>& stream)
	: project{ project }
	, document{ stream }
{
}

void Translation_module::process()
{
    lexical_analyze();
    syntax_analyze();
}

void Translation_module::lexical_analyze()
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

void Translation_module::syntax_analyze()
{
    Parser parser(&tokens[0]);
    while (true)
    {
        auto statement = parser.parse_next_statement();
        if (statement == nullptr) break;
        statements.push_back(statement);
    } 

    for (auto statement : statements)
    {
        std::cout << statement->is_valid << std::endl;
    }
}