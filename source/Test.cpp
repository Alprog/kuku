
#include "test.h"

#include "streams.h"
#include "unicode_streams.h"
#include "text_document.h"
#include <fstream>
#include "parser.h"

#include "virtual_machine.h"
#include "string.h"
#include "chunk.h"
#include "instruction_type.h"
#include "routine.h"

#include "source_project.h"

#include "mem/tracker.h"
#include "Instructions.h"

void test()
{
	Chunk chunk;
	chunk.write(Instruction_PUSH_INT{111});
	chunk.write(Instruction_PUSH_INT{222});
	chunk.write(Instruction_INT_ADD{});
	chunk.write(Instruction_PRINT{0});

	chunk.write(Instruction_PUSH_INT{ 2 });
	chunk.write(Instruction_PUSH_INT{ 4 });
	chunk.write(Instruction_INT_POWER{});
	chunk.write(Instruction_PRINT{1});
	chunk.write(Instruction_END{});

	Routine routine(chunk.get_start_pointer());	
	routine.run();



	String s1("abc");
	String s2(u"abc");
	String s3(U"abc");

	auto a1 = s1.get_character(1);
	auto a2 = s2.get_character(1);
	auto a3 = s3.get_character(1);

	source_project project;
	project.add_file("C:/kuku/data/main.kuku");
	project.process_all();
	project.print_info();

	project.clear_all();
}