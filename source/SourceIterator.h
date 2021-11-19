#pragma once

#include <vector>
#include "types.h"
#include "Encoding.h"
#include "Position.h"

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