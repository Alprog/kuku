
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

void test()
{
	Chunk chunk;
	chunk.write(Instruction_type::INT_SET);
	chunk.write((byte)0);
	chunk.write((integer)111);

	chunk.write(Instruction_type::INT_SET);
	chunk.write((byte)1);
	chunk.write((integer)222);

	chunk.write(Instruction_type::INT_ADD);
	chunk.write((byte)0);
	chunk.write((byte)1);
	chunk.write((byte)2);

	chunk.write(Instruction_type::PRINT);
	chunk.write((byte)2);

	chunk.write(Instruction_type::END);

	Routine routine(chunk.get_start_pointer());	
	//routine.run();



	String s1("abc");
	String s2(u"abc");
	String s3(U"abc");

	auto a1 = s1.get_character(1);
	auto a2 = s2.get_character(1);
	auto a3 = s3.get_character(1);


	std::basic_ifstream<byte> file_stream("C:/kuku/data/main.kuku");
	Basic_input_stream basic_stream(file_stream);
	unicode::Utf8to16_stream u16stream(basic_stream);

	Text_document document(u16stream);

	Lexer lexer(document);
	Parser parser(lexer);

	parser.process();
}