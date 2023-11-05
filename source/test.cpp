
#include "test.h"

#include "streams.h"
#include "unicode_streams.h"
#include "text_document.h"
#include <fstream>
#include "parser.h"

#include "virtual_machine.h"
#include "string.h"
#include "bytecode.h"
#include "opcode.h"
#include "routine.h"

#include "source_project.h"

#include "mem/tracker.h"
#include "instructions.h"
#include <memory>
#include "base64.h"
#include "guid.h"

#include "console.h"

void test_old()
{
	virtual_machine machine;

	rt::function function;
	function.name = "test";

	auto& bytecode = function.bytecode;
	bytecode.instructions.push_back(instruction_SET_INT{ 0, 111 });
 	bytecode.instructions.push_back(instruction_SET_INT{ 1, 222 });
	bytecode.instructions.push_back(instruction_INT_ADD{ 0, 0, 1 });
	bytecode.instructions.push_back(instruction_PRINT{ 0 });

	bytecode.instructions.push_back(instruction_SET_INT{ 0, 2 });
	bytecode.instructions.push_back(instruction_SET_INT{ 1, 4 });
	bytecode.instructions.push_back(instruction_INT_POWER{ 0, 0, 1 });
	bytecode.instructions.push_back(instruction_PRINT{ 0 });
	bytecode.instructions.push_back(instruction_END{});

	auto& routine = machine.create_routine(function);
	routine.run();

	kuku::string s1("abc");
	kuku::string s2(u"abc");
	kuku::string s3(U"abc");

	auto a1 = s1.get_character(1);
	auto a2 = s2.get_character(1);
	auto a3 = s3.get_character(1);
	s3.try_shrink();
	auto a3s = s3.get_character(1);


	source_project project;
	project.add_file("C:/kuku/data/main.kuku");
	project.process_all();
	project.print_info();

	project.clear_all();

	guid g("Aze4gmnP");
	auto a = g.to_string();

	object_header header(0);
	header.class_index = 0x7777;
	header.packed_guid[0] = 0xAA;
	header.packed_guid[1] = 0xBB;
	header.packed_guid[2] = 0xCC;
	header.packed_guid[3] = 0xDD;
	header.packed_guid[4] = 0xEE;
	header.packed_guid[5] = 0xFF;

	guid gg = header.get_guid();
	guid ggg = guid(gg.value);
}

void test()
{
	while (true)
	{
		virtual_machine machine;

		source_project project;
		project.add_file("C:/kuku/data/test.kuku");
		project.process_all();

		chunk chunk = project.get_module("C:/kuku/data/test.kuku")->compile_to_chunk();

		chunk.functions[0].full_dump();

		console::read_line();

		auto& routine = machine.create_routine(chunk.functions[0]);
		routine.run();

		console::read_line();
	}
}