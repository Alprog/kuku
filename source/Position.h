#pragma once

#include "json.h"

#include "JsonSerializable.h"
#include "JsonField.h"
#include "JsonScheme.h"
#include <string>

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

    std::u16string toStr()
    {
        auto asciiStr = "{" + std::to_string(line) + ":" + std::to_string(character) + "}";
        return std::u16string(std::begin(asciiStr), std::end(asciiStr));
    }

    JSCHEME(Position, JFIELD(line), JFIELD(character))
};