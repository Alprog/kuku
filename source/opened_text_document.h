#pragma once

#include <string>
#include "json_serializable.h"
#include "json_scheme.h"

class Opened_text_document : public Json_serializable
{
public:
    std::string uri;
    std::string languageId;
    int version;
    std::string text;

    JSCHEME(Opened_text_document, JFIELD(uri), JFIELD(languageId), JFIELD(version), JFIELD(text))
};