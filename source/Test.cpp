
#include "Test.h"

#include "Streams.h"
#include "UnicodeStreams.h"
#include "TextDocument.h"
#include <fstream>
#include "Lexer.h"

void Test()
{
	std::basic_ifstream<byte> fileStream("C:/Users/alpro/Desktop/efef.kuku");
	BasicInputStream basicStream(fileStream);
	unicode::Utf8To16Stream u16stream(basicStream);

	TextDocument document(u16stream);

	Lexer lexer(document);
	lexer.process();
}