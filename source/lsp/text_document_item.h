
#pragma once

#include <string>
#include "json/serializable.h"
#include "json/scheme.h"

namespace lsp
{
    struct text_document_item : public json::serializable
    {
        std::string uri;
        std::string language_id;
        int version;
        std::u8string text;

        JSCHEME(uri, language_id, version, text)
    };
}