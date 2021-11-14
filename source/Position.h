#pragma once

#include "json.h"

#include "JsonSerializable.h"
#include "JsonField.h"
#include "JsonScheme.h"

class Position : public JsonSerializable
{
public:
    Position(int line = 0, int character = 0)
        : line{ line }
        , character{ character }
    {
    }

    int line;
    int character;

    JSCHEME(Position, JFIELD(line), JFIELD(character))
};