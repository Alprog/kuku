#pragma once

#include <vector>
#include "types.h"
#include "encoding.h"
#include "lsp/position.h"

class Text_document;

class Source_iterator
{
public:
    Source_iterator& operator++();   // pre
    Source_iterator operator++(int); // post

    Source_iterator(Text_document& text_document);

    utf16unit operator*();

    lsp::position position;
    Text_document& text_document;
};