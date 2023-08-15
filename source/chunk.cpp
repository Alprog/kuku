
#include "chunk.h"
#include "jump_table.h"
#include "console.h"

byte* chunk::get_start_pointer()
{
	return &bytes[0];
}

void chunk::print_instructions()
{
	byte* ptr = get_start_pointer();
	while (ptr - get_start_pointer() < bytes.size())
	{
		auto info = jump_table::get_info_function[*ptr]();
		console::write_line(info->to_string(ptr));
		ptr += jump_table::get_size_function[*ptr]();
	}
}