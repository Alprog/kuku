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
	int index = 0;
	for (auto& instruction : bytecode.instructions)
	{
		auto info = jump_table::get_info_function[instruction.I]();

		auto line = std::format("{:3} | {:27}| ", index++, info->to_string(instruction));

		console::write_line(line);
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
			auto jump_offset = reinterpret_cast<instruction_JUMP*>(ptr)->A;
			return std::to_string(offset + jump_offset);
		}

		case instruction_type::MOVE:
		{
			auto a = reinterpret_cast<instruction_MOVE*>(ptr)->A;
			auto b = reinterpret_cast<instruction_MOVE*>(ptr)->B;
			std::u16string nameA = get_local_info(offset, a).name;
			std::u16string nameB = get_local_info(offset, b).name;
			std::u16string line = nameA + u" = " + nameB;
			return std::string(std::begin(line), std::end(line));
		}

		case instruction_type::INT_ADD:
		case instruction_type::LESS:
		{
			auto a = reinterpret_cast<instruction_INT_ADD*>(ptr)->A;
			auto b = reinterpret_cast<instruction_INT_ADD*>(ptr)->B;
			auto c = reinterpret_cast<instruction_INT_ADD*>(ptr)->C;
			std::u16string nameA = get_local_info(offset, a).name;
			std::u16string nameB = get_local_info(offset, b).name;
			std::u16string nameC = get_local_info(offset, c).name;
			std::u16string line = nameA + u" = " + nameB + u" op " + nameC;
			return std::string(std::begin(line), std::end(line));
		}

	};

	return "";
}