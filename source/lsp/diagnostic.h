
#pragma once

#include <string>
#include "json/serializable.h"
#include "json/field.h"
#include "json/scheme.h"
#include "enums.h"
#include "range.h"

namespace lsp
{
    struct diagnostic : public json::serializable
    {
        diagnostic(lsp::range range, diagnostic_severity severity, int code, std::string message);

        lsp::range range;
        diagnostic_severity severity;
        int code;
        std::string message;
        
        JSCHEME(range, severity, code, message)
    };
}