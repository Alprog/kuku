#pragma once

#include <string>

namespace rt
{
	class localvar_info
	{
		std::string name;
		int start_instruction;
		int end_instruction;
	};
}