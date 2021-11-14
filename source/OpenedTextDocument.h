#pragma once

#include <string>
#include "JsonSerializable.h"
#include "JsonScheme.h"

class OpenedTextDocument : public JsonSerializable
{
public:
    std::string uri;
    std::string languageId;
    int version;
    std::string text;

    JSCHEME(OpenedTextDocument, JFIELD(uri), JFIELD(languageId), JFIELD(version), JFIELD(text))
};