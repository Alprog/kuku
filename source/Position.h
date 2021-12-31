#pragma once

#include "json.h"

#include "json_serializable.h"
#include "json_field.h"
#include "json_scheme.h"
#include <string>

class Position : public Json_serializable
{
public:
    Position(int line = 0, int character = 0);

    int line;
    int character;

    std::u16string to_str();

    std::strong_ordering operator<=>(const Position& other) const;
    
    JSCHEME(Position, JFIELD(line), JFIELD(character))
};