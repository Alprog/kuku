
#pragma once

#include <string>
#include "json/serializable.h"
#include "json/scheme.h"

namespace lsp
{
    struct text_document_identifier : public json::serializable
    {
        std::string uri;

        JSCHEME(text_document_identifier, JFIELD(uri))
    };
}