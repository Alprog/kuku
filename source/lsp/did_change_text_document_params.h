
#pragma once

#include <vector>
#include "json/serializable.h"
#include "json/scheme.h"
#include "lsp/text_document_content_change_event.h"

namespace lsp
{
    struct did_change_text_document_params : public json::serializable
    {
        std::vector<lsp::text_document_content_change_event> contentChanges;

        JSCHEME(did_change_text_document_params, JFIELD(contentChanges))
    };
}