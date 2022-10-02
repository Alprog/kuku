
#include "translation_module.h"

#include "source_project.h"
#include "console.h"
#include "scope_analyzer.h"
#include "compiler.h"
#include "err/error.h"

translation_module::translation_module(source_project& project, Input_stream<utf16unit>& stream)
	: project{ project }
	, document{ stream }
    , root_scope{ nullptr, scope_type::module_root }
{
}

translation_module::~translation_module()
{
    clear();
}

void translation_module::process()
{
    tokenize();
    parse_statements();
    analyze_scope();
    analyze_semantic();
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
    Parser parser(*this, &tokens[0]);
    while (true)
    {
        auto statement = parser.parse_next_statement();
        if (statement == nullptr) break;
        statements.push_back(statement);
    }
}

void translation_module::analyze_scope()
{
    scope_analyzer analyzer(*this, statements);
    analyzer.analyze();
}

void translation_module::analyze_semantic()
{

}

void translation_module::compile()
{
    compiler compiler(*this);
    compiler.compile();
}

void translation_module::compile_and_run()
{
    try
    {
        compiler compiler(*this);
        compiler.compile();

        compiler.chunk.write(Instruction_PRINT{});
        compiler.chunk.write(Instruction_END{});

        Routine routine{ compiler.chunk.get_start_pointer() };
        routine.run();
    }
    catch (error& error)
    {
        Console::write_line(error.get_message());
    }
}

void translation_module::clear()
{
    for (auto& token : tokens)
    {
        delete token;
    }
    tokens.clear();
    for (auto& statement : statements)
    {
        delete statement;
    }
    statements.clear();
}

void translation_module::print_statements()
{
    for (auto statement : statements)
    {
        auto line = statement->get_statement_type() + u" " + (statement->is_valid ? u"1" : u"0");
        Console::write_line(line);

        if (!statement->is_valid)
        {
            Console::write_line(statement->error_text);
        }
    }
}

token* translation_module::get_token(lsp::position position)
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

stmt::statement* translation_module::get_statement(lsp::position position)
{
    for (auto statement : statements)
    {
        if (statement->get_full_range().contains(position))
        {
            return statement;
        }
    }
    return nullptr;
}