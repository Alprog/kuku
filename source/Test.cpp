
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
	chunk.write(Instruction<Instruction_type::INT_SET>{111});
	chunk.write(Instruction<Instruction_type::INT_SET>{222});
	chunk.write(Instruction<Instruction_type::INT_ADD>{0, 1, 2});
	chunk.write(Instruction<Instruction_type::PRINT>{2});
	chunk.write(Instruction<Instruction_type::END>{});

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