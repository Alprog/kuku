#pragma once

#include "json.h"

#include "JsonSerializable.h"
#include "JsonField.h"
#include "JsonScheme.h"

#define ARG(memberName) new JsonField{ #memberName, &Self::memberName }

#define SCHEME(Class, ...) \
    virtual JsonScheme& GetJsonScheme() override \
    { \
        using Self = Class; \
        static auto scheme = JsonScheme( { __VA_ARGS__ } ); \
        return scheme; \
    } \

class Position : public JsonSerializable
{
public:
    unsigned int line;
    unsigned int character;

    SCHEME(Position, ARG(line), ARG(character))
};