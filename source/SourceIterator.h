#pragma once

#include <vector>
#include "primitives.h"
#include "Encoding.h"
#include "Position.h"
#include <cstdint>

class TextDocument;

class SourceIterator
{
public:
    SourceIterator(TextDocument& textDocument);
    void next();

    uint16_t operator*();

    Position position;
    TextDocument& textDocument;
};