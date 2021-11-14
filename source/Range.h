#pragma once

#include "JsonSerializable.h"
#include "Position.h"

class Range : public JsonSerializable
{
public:
    Position start;
    Position end;

    JSCHEME(Range, JFIELD(start), JFIELD(end))
};