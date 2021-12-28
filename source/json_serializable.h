#pragma once

#include "json.h"

class Json_scheme;

class Json_serializable
{
public:
    nlohmann::json to_json();
    void read_fields(nlohmann::json& json);

    virtual Json_scheme& get_json_scheme() = 0;
};

template <typename ResultType>
ResultType from_json(nlohmann::json& json)
{
    ResultType instance;
    instance.read_fields(json);
    return instance;
}
template<> int from_json<int>(nlohmann::json& json);
template<> float from_json<float>(nlohmann::json& json);
template<> std::string from_json<std::string>(nlohmann::json& json);

#define JFIELD(memberName) new Json_field{ #memberName, &Self::memberName }

#define JSCHEME(Class, ...) \
    virtual Json_scheme& get_json_scheme() override \
    { \
        using Self = Class; \
        static auto scheme = Json_scheme( { __VA_ARGS__ } ); \
        return scheme; \
    }
