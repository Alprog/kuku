#include "function.h"

#include "console.h"
#include "unicode.h"
#include <format>
#include "jump_table.h"
#include "unicode.h"
#include "instructions.h"
#include <functional>

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


		auto comment = get_comment(index, instruction, info->comment);

		auto line = std::format("{:3} | {:27} | ", index++, info->to_string(instruction));

		if (include_comments)
		{
			line += comment;
		}

		console::write_line(line);
	}
}

void rt::function::print_locals_info()
{
	console::write_line("TYPE OFFSET START END NAME");

	for (auto& info : locals)
	{
		auto record = std::format("{:<4} {:<6} {:<5} {:<4}", (int)info.type_index, info.stack_offset, info.start_instruction, info.end_instruction);
		console::write(record);
		console::write_line(info.name);
	}
}

bool perform_replacement(std::string& comment, base_instruction& instruction, std::string macro_name, std::function<std::string(int)> macro)
{
	auto macro_start = comment.find(macro_name + "(");
	if (macro_start != std::string::npos)
	{
		auto macro_end = comment.find(")", macro_start) + 1;
		auto arg_start = macro_start + macro_name.size() + 1;
		auto arg_name = comment.substr(arg_start, macro_end - arg_start - 1);
		auto arg_value = instruction.get_argument_value(arg_name);
		comment.replace(macro_start, macro_end - macro_start, macro(arg_value));
		return true;
	}
	return false;
}

std::string rt::function::get_comment(int index, base_instruction& instruction, std::string comment)
{
	auto R = [&](int value)
	{
		auto name = get_local_info(index, value).name;
		return std::string(std::begin(name), end(name));
	};

	auto INT = [&](int value) { return std::to_string(value); };

	auto JMP = [&](int value)
	{
		return std::to_string(index + value);
	};

	while (perform_replacement(comment, instruction, "R", R)) {}
	while (perform_replacement(comment, instruction, "INT", INT)) {}
	while (perform_replacement(comment, instruction, "JMP", JMP)) {}

	return comment;
}