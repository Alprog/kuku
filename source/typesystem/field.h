
#pragma once

#include "typesystem/info.h"

namespace typesystem
{
	class type;

	class field : public typesystem::info
	{
	public:
		std::u8string name;
		typesystem::type* type;
	};
};