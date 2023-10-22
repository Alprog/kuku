
#include "bytecode.h"
#include "jump_table.h"
#include "console.h"
#include <format>

byte* bytecode::get_start_pointer()
{
	return &bytes[0];
}

void bytecode::print_instructions()
{
	byte* ptr = get_start_pointer();
	while (ptr - get_start_pointer() < bytes.size())
	{
		auto info = jump_table::get_info_function[*ptr]();

		int offset = ptr - get_start_pointer();
		
		auto line = std::format("{:3} {}", offset, info->to_string(ptr));

		console::write_line(line);
		ptr += jump_table::get_size_function[*ptr]();
	}
}