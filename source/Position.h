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

    Position(nlohmann::json json)
    {
        auto a = JsonField("line", &Position::line);
        unsigned int  b = 3;
        a.set(*this, b);

        auto& g = a.get(*this);

        line = json["line"].get<unsigned int>();
        character = json["character"].get<unsigned int>();
    }
};