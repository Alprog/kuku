#pragma once

#include <string>
#include "json_serializable.h"
#include "json_scheme.h"

class OpenedTextDocument : public JsonSerializable
{
public:
    std::string uri;
    std::string languageId;
    int version;
    std::string text;

    JSCHEME(OpenedTextDocument, JFIELD(uri), JFIELD(languageId), JFIELD(version), JFIELD(text))
};