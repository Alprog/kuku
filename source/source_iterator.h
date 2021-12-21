#pragma once

#include <vector>
#include "types.h"
#include "encoding.h"
#include "position.h"

class TextDocument;

class SourceIterator
{
public:
    SourceIterator& operator++();
    SourceIterator operator++(int);

    SourceIterator(TextDocument& textDocument);

    utf16unit operator*();

    Position position;
    TextDocument& textDocument;
};