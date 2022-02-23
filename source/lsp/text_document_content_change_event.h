
#pragma once

#include <string>
#include "lsp/range.h"
#include "json/serializable.h"
#include "json/scheme.h"

namespace lsp
{
    struct text_document_content_change_event : public json::serializable
    {
        range range;
        std::u16string text;

        JSCHEME(range, text)
    };
}