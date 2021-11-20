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
class BasicInputStream : public InputStream<T>
{
public:
	std::basic_istream<T>& stream;

	BasicInputStream(std::basic_istream<T>& stream)
		: stream { stream }
	{
	}

	virtual bool next(T& outCharacter) override
	{
		stream.get(outCharacter);
		return !stream.fail();
	}
};
