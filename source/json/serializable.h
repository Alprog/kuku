
#pragma once

#include "json/object.h"
#include <type_traits>

namespace json
{
    class scheme;

    class serializable
    {
    public:
        json::object to_json();
        void read_fields(json::object& json);

        virtual json::scheme& get_json_scheme() = 0;
    };
}

#include "is_vector.h"

template <typename T>
concept vector_type = is_vector<T>::value;

template <typename ResultType>
ResultType from_json(json::object& object)
{
    ResultType instance;
    instance.read_fields(object);
    return instance;
}

template<> int from_json<int>(json::object& object);
template<> float from_json<float>(json::object& object);
template<> std::string from_json<std::string>(json::object& object);
template<> std::u8string from_json<std::u8string>(json::object& object);
template<> std::u16string from_json<std::u16string>(json::object& object);

template <vector_type VectorType>
VectorType from_json(json::object& object)
{
    if (object.is_array())
    {
        VectorType vector;
        for (int i = 0; i < object.size(); i++)
        {
            vector.push_back(from_json<VectorType::value_type>(object[i]));
        }
        return vector;
    }
    throw new std::exception("not array");
}

#define JFIELD(memberName) new json::field{ #memberName, &Self::memberName }

#define JSCHEME(...) \
virtual json::scheme& get_json_scheme() override \
{ \
    using Self = std::remove_pointer_t<decltype(this)>; \
    static auto scheme = json::scheme( { __VA_ARGS__ } ); \
    return scheme; \
}
