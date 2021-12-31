
#pragma once

#include "json_serializable.h"
#include "position.h"

class Range : public Json_serializable
{
public:
    Range(Position start, Position end);

    bool contains(Position position);

    Position start;
    Position end;

    JSCHEME(Range, JFIELD(start), JFIELD(end))
};