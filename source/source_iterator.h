#pragma once

#include <vector>
#include "types.h"
#include "encoding.h"
#include "position.h"

class Text_document;

class Source_iterator
{
public:
    Source_iterator& operator++();
    Source_iterator operator++(int);

    Source_iterator(Text_document& text_document);

    utf16unit operator*();

    Position position;
    Text_document& text_document;
};