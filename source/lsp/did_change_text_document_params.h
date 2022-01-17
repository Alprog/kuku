
#pragma once

#include <vector>
#include "json/serializable.h"
#include "json/scheme.h"
#include "lsp/text_document_content_change_event.h"
#include "lsp/versioned_text_document_identifier.h"

namespace lsp
{
    struct did_change_text_document_params : public json::serializable
    {
        lsp::versioned_text_document_identifier text_document;
        std::vector<lsp::text_document_content_change_event> content_changes;

        JSCHEME(did_change_text_document_params, JFIELD(text_document), JFIELD(content_changes))
    };
}