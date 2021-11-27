
#include "Test.h"

#include "Streams.h"
#include "UnicodeStreams.h"
#include "TextDocument.h"
#include <fstream>
#include "Parser.h"

#include "VirtualMachine.h"
#include "String.h"

void Test()
{
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