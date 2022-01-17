
#pragma once

#include <string>
#include "lsp/range.h"
#include "json/serializable.h"
#include "json/scheme.h"

namespace lsp
{
    class text_document_content_change_event : public json::serializable
    {
    public:
        range range;
        std::u16string text;

        JSCHEME(text_document_content_change_event, JFIELD(range), JFIELD(text))
    };
}