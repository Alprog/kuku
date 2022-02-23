
#pragma once

#include <string>
#include "json/serializable.h"
#include "json/scheme.h"

namespace lsp
{
    struct versioned_text_document_identifier : public json::serializable
    {
        std::string uri;
        int version;

        JSCHEME(JFIELD(uri), JFIELD(version))
    };
}