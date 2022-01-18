#pragma once

namespace lsp
{
    enum class text_document_sync_kind
    {
        None = 0,
        Full = 1,
        Incremental = 2
    };
}