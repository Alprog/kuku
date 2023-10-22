#include "function.h"

#include "console.h"
#include "unicode.h"
#include <format>

void rt::function::print_locals_info()
{
	console::write_line("TYPE OFFSET START END NAME");

	for (auto& info : locals)
	{
		auto record = std::format("{:<4} {:<6} {:<5} {:<3} ", (int)info.type_index, info.stack_offset, info.start_instruction, info.end_instruction);
		console::write(record);
		console::write_line(info.name);
	}	
}