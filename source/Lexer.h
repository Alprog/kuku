#pragma once

#include <string>
#include "token.h"
#include "token_type.h"
#include "types.h"
#include "text_document.h"
#include "source_iterator.h"

class Lexer
{
public:
    Lexer(Text_document& text_document);
    token* get_next_token();

public:
    token* finish_line_comment(Source_iterator start_it);
    token* finish_block_comment(Source_iterator start_it);
    token* finish_binding_block_comment(Source_iterator start_it);
    token* finish_string(Source_iterator start_it, utf16unit end_quote, bool escaping);

    bool match(utf16unit symbol);

    bool move_after(utf16unit end_symbol);
    bool move_after_escaped(utf16unit end_symbol);

    token* create_token(Source_iterator start, Token_type type);

    Text_document& text_document;
    Source_iterator it;
};