
#include "Test.h"

#include "Streams.h"
#include "UnicodeStreams.h"
#include "TextDocument.h"
#include <fstream>
#include "Parser.h"

#include "VirtualMachine.h"
#include "String.h"
#include "Chunk.h"
#include "Instruction.h"
#include "Routine.h"

void Test()
{
	Chunk chunk;
	chunk.write(Instruction::int_set);
	chunk.write((byte)0);
	chunk.write((integer)111);

	chunk.write(Instruction::int_set);
	chunk.write((byte)1);
	chunk.write((integer)222);

	chunk.write(Instruction::int_add);
	chunk.write((byte)0);
	chunk.write((byte)1);
	chunk.write((byte)2);

	chunk.write(Instruction::print);
	chunk.write((byte)2);

	chunk.write(Instruction::end);

	Routine routine(chunk.getStartPointer());	
	routine.run();



	String s1("abc");
	String s2(u"abc");
	String s3(U"abc");

	auto a1 = s1.getCharacter(1);
	auto a2 = s2.getCharacter(1);
	auto a3 = s3.getCharacter(1);


	std::basic_ifstream<byte> fileStream("C:/Users/alpro/Desktop/efef.kuku");
	BasicInputStream basicStream(fileStream);
	unicode::Utf8To16Stream u16stream(basicStream);

	TextDocument document(u16stream);

	Lexer lexer(document);
	Parser parser(lexer);

	parser.process();
}