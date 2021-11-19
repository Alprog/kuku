
#include "Test.h"

#include "Streams.h"
#include "UnicodeStreams.h"
#include "TextDocument.h"

void Test()
{
	FileInputStream<byte> fileStream("C:/Users/alpro/Desktop/efef.kuku");
	unicode::Utf8To16Stream u16stream(fileStream);

	TextDocument document(u16stream);
}