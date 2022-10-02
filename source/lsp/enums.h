#pragma once

namespace lsp
{
    enum class text_document_sync_kind
    {
        None = 0,
        Full = 1,
        Incremental = 2
    };

    enum class diagnostic_severity
    {
		Error = 1,
	    Warning = 2,
	    Information = 3,
	    Hint = 4
    };
}