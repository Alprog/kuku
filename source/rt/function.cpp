#include "function.h"

#include "console.h"
#include "unicode.h"
#include <format>
#include "jump_table.h"
#include "unicode.h"
#include "instructions.h"

const rt::localvar_info& rt::function::get_local_info(int instruction_offset, int stack_offset) const
{
	for (const auto& info : locals)
	{
		if (info.stack_offset == stack_offset)
		{
			if (instruction_offset >= info.start_instruction && instruction_offset < info.end_instruction)
			{
				return info;
			}
		}
	}

	static localvar_info unknown_info { u"unknown" };
	return unknown_info;
}

void rt::function::print_instructions(bool include_comments)
{
	int stack_size = 0;

	byte* ptr = bytecode.get_start_pointer();
	while (ptr - bytecode.get_start_pointer() < bytecode.bytes.size())
	{
		auto info = jump_table::get_info_function[*ptr]();
		stack_size += info->stack_change;

		int offset = ptr - bytecode.get_start_pointer();

		auto line = std::format("{:3} | {:18} | {:1} | ", offset, info->to_string(ptr), stack_size);

		if (include_comments)
		{
			auto comment = get_comment(ptr, info->type, offset);
			if (!comment.empty())
			{
				line = std::format("{} | ({})", line, comment);
			}
		}

		console::write_line(line);
		ptr += jump_table::get_size_function[*ptr]();
	}
}

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

std::string rt::function::get_comment(byte* ptr, instruction_type type, int offset)
{
	switch (type)
	{
		case instruction_type::JUMP:
		case instruction_type::JUMP_ON_FALSE:
		{
			auto jump_offset = reinterpret_cast<instruction_JUMP*>(ptr)->jump_offset;
			return std::to_string(offset + jump_offset);
		}

		case instruction_type::GET_LOCAL:
		case instruction_type::SET_LOCAL:
		{
			auto index = reinterpret_cast<instruction_SET_LOCAL*>(ptr)->index;
			std::u16string name = get_local_info(offset, index).name;
			return std::string(std::begin(name), std::end(name));
		}

		case instruction_type::SET_LOCAL_REG:
			auto a = reinterpret_cast<instruction_SET_LOCAL_REG*>(ptr)->a;
			auto b = reinterpret_cast<instruction_SET_LOCAL_REG*>(ptr)->b;
			std::u16string nameA = get_local_info(offset, a).name;
			std::u16string nameB = get_local_info(offset, b).name;
			std::u16string line = nameA + u" " + nameB;
			return std::string(std::begin(line), std::end(line));

	};

	return "";
}