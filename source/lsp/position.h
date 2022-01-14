#pragma once

#include <string>
#include "json/serializable.h"
#include "json/field.h"
#include "json/scheme.h"

namespace lsp
{
    class position : public json::serializable
    {
    public:
        position(int line = 0, int character = 0);

        int line;
        int character;

        std::u16string to_str();

        std::strong_ordering operator<=>(const position& other) const;

        JSCHEME(position, JFIELD(line), JFIELD(character))
    };
}