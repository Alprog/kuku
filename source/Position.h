#pragma once

#include "json.h"

#include "JsonSerializable.h"
#include "JsonField.h"
#include "JsonScheme.h"

class Position : public JsonSerializable
{
public:
    int line;
    int character;

    JSCHEME(Position, JFIELD(line), JFIELD(character))
};