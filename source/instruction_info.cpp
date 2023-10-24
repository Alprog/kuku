
#include "instruction_info.h"
#include "instruction_type.h"
#include <sstream>

std::string instruction_info::to_string(byte* ptr)
{
	std::stringstream ss;

	ss << name;
	ptr += sizeof(instruction_type);
	for (auto& arg : arguments)
	{
		ss << " " << arg->to_string(ptr);
		ptr += arg->get_size();
	}

	return ss.str();
}
