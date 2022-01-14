
#pragma once

#include <string>
#include "json/serializable.h"
#include "json/scheme.h"

namespace lsp
{
    class text_document_item : public json::serializable
    {
    public:
        std::string uri;
        std::string languageId;
        int version;
        std::u8string text;

        JSCHEME(text_document_item, JFIELD(uri), JFIELD(languageId), JFIELD(version), JFIELD(text))
    };
}