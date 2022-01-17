
#pragma once

#include <vector>
#include <string>
#include "utils.h"

template <typename T>
struct Enum_reflector
{
};

#define Reflectable_enum(EnumName, ...) \
	enum class EnumName { __VA_ARGS__ }; \
	template <> \
	struct Enum_reflector<EnumName> \
	{ \
		static std::string get_enum_name(EnumName value) \
		{ \
			static auto vector = split<std::string>(#__VA_ARGS__, ", "); \
			return vector[(int)value]; \
		}; \
	};

template <typename EnumT>
std::string get_name(EnumT value)
{
	return Enum_reflector<EnumT>::get_enum_name(value);
};

template <typename EnumT>
std::u8string get_u8name(EnumT value)
{
	auto name = Enum_reflector<EnumT>::get_enum_name(value);
	return std::u8string(std::begin(name), std::end(name));
};