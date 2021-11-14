#pragma once

#include "json.h"

class JsonScheme;

class JsonSerializable
{
public:
    nlohmann::json toJson();
    void readFields(nlohmann::json& json);

    virtual JsonScheme& GetJsonScheme() = 0;
};

template <typename ResultType>
ResultType fromJson(nlohmann::json& json)
{
    ResultType instance;
    instance.readFields(json);
    return instance;
}
template<> int fromJson<int>(nlohmann::json& json);
template<> float fromJson<float>(nlohmann::json& json);
template<> std::string fromJson<std::string>(nlohmann::json& json);

#define JFIELD(memberName) new JsonField{ #memberName, &Self::memberName }

#define JSCHEME(Class, ...) \
    virtual JsonScheme& GetJsonScheme() override \
    { \
        using Self = Class; \
        static auto scheme = JsonScheme( { __VA_ARGS__ } ); \
        return scheme; \
    }
