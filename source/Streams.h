#pragma once

#include <string.h>
#include "types.h"
#include <iostream>
#include <fstream>

template <typename T>
class InputStream
{
public:
	virtual bool next(T& outCharacter) = 0;
};

template <typename T>
class FileInputStream : public InputStream<T>
{
public:
	std::basic_fstream<T> fs;

	FileInputStream(std::string filePath)
	{
		fs.open(filePath);
	}

	~FileInputStream()
	{
		fs.close();
	}

	virtual bool next(T& outCharacter) override
	{
		if (fs.eof())
			return false;

		fs.get(outCharacter);
		return true;
	}
};
