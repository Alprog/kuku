#pragma once

#include "json_serializable.h"
#include "position.h"

class Range : public JsonSerializable
{
public:
    Range(Position start, Position end)
        : start{ start }
        , end{ end }
    {
    }

    Position start;
    Position end;

    JSCHEME(Range, JFIELD(start), JFIELD(end))
};