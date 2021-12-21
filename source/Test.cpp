
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

void Test()
{
	Chunk chunk;
	chunk.write(InstructionType::INT_SET);
	chunk.write((byte)0);
	chunk.write((integer)111);

	chunk.write(InstructionType::INT_SET);
	chunk.write((byte)1);
	chunk.write((integer)222);

	chunk.write(InstructionType::INT_ADD);
	chunk.write((byte)0);
	chunk.write((byte)1);
	chunk.write((byte)2);

	chunk.write(InstructionType::PRINT);
	chunk.write((byte)2);

	chunk.write(InstructionType::END);

	Routine routine(chunk.getStartPointer());	
	//routine.run();



	String s1("abc");
	String s2(u"abc");
	String s3(U"abc");

	auto a1 = s1.getCharacter(1);
	auto a2 = s2.getCharacter(1);
	auto a3 = s3.getCharacter(1);


	std::basic_ifstream<byte> fileStream("C:/kuku/data/main.kuku");
	BasicInputStream basicStream(fileStream);
	unicode::Utf8To16Stream u16stream(basicStream);

	TextDocument document(u16stream);

	Lexer lexer(document);
	Parser parser(lexer);

	parser.process();
}