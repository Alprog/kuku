

#pragma once

#include "typesystem/info.h"
#include <string>

namespace typesystem
{
	class variable : public typesystem::info
	{
	public:
		std::u8string name;
		typesystem::type* type;
	};
};