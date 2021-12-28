#pragma once

#include <string.h>
#include "types.h"
#include <iostream>
#include <fstream>

template <typename T>
class Input_stream
{
public:
	virtual bool next(T& out_character) = 0;
};

template <typename T>
class Basic_input_stream : public Input_stream<T>
{
public:
	std::basic_istream<T>& stream;

	Basic_input_stream(std::basic_istream<T>& stream)
		: stream { stream }
	{
	}

	virtual bool next(T& out_character) override
	{
		stream.get(out_character);
		return !stream.fail();
	}
};
