#pragma once

#include <string.h>
#include <cstdint>
#include "primitives.h"
#include "Unicode.h"
#include <iostream>
#include <fstream>

template <typename T>
class InputStream
{
public:
	virtual bool next(T& outCharacter) = 0;
};

template <typename T>
class FileInputStream : InputStream<T>
{
public:
	std::basic_fstream<T> fs;

	FileInputStream(std::string filePath)
	{
		fs.open(filePath);
	}

	virtual bool next(T& outCharacter) override
	{
		if (fs.eof())
			return false;

		fs.get(outCharacter);
		return true;
	}
};


/*class Utf8ToStream
{
public:
	InputStream stream;

	virtual bool next(uint16_t& outCharacter)
	{
		character c = unicode::readUTF8(stream);
	
		unicode::writeUTF16(c, )
	}
};*/