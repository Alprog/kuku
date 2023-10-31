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

	static std::vector<localvar_info> temporaries;
	if (temporaries.size() == 0)
	{
		for (int i = 0; i < 100; i++)
		{
			auto name = "%" + std::to_string(i);
			temporaries.push_back( { std::u16string(std::begin(name), std::end(name)) } );
		}
	}

	return temporaries[stack_offset];
}

void rt::function::print_instructions(bool include_comments)
{
	byte* ptr = bytecode.get_start_pointer();
	while (ptr - bytecode.get_start_pointer() < bytecode.bytes.size())
	{
		auto info = jump_table::get_info_function[*ptr]();
		int offset = ptr - bytecode.get_start_pointer();

		auto line = std::format("{:3} | {:18} |", offset, info->to_string(ptr));

		if (include_comments)
		{
			auto comment = get_comment(ptr, info->type, offset);
			if (!comment.empty())
			{
				line = std::format("{} {}", line, comment);
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
		auto record = std::format("{:<4} {:<6} {:<5} {:<3}", (int)info.type_index, info.stack_offset, info.start_instruction, info.end_instruction);
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
		{
			auto a = reinterpret_cast<instruction_SET_LOCAL_REG*>(ptr)->a;
			auto b = reinterpret_cast<instruction_SET_LOCAL_REG*>(ptr)->b;
			std::u16string nameA = get_local_info(offset, a).name;
			std::u16string nameB = get_local_info(offset, b).name;
			std::u16string line = nameA + u" = " + nameB;
			return std::string(std::begin(line), std::end(line));
		}

		case instruction_type::INT_ADD_REG:
		case instruction_type::LESS_REG:
		{
			auto a = reinterpret_cast<instruction_INT_ADD_REG*>(ptr)->a;
			auto b = reinterpret_cast<instruction_INT_ADD_REG*>(ptr)->b;
			auto c = reinterpret_cast<instruction_INT_ADD_REG*>(ptr)->c;
			std::u16string nameA = get_local_info(offset, a).name;
			std::u16string nameB = get_local_info(offset, b).name;
			std::u16string nameC = get_local_info(offset, c).name;
			std::u16string line = nameA + u" = " + nameB + u" op " + nameC;
			return std::string(std::begin(line), std::end(line));
		}

	};

	return "";
}