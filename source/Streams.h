#pragma once

#include <string.h>
#include "types.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

template <typename T>
class Input_stream
{
public:
	virtual bool read(T& out_value) = 0;
};

template <typename T>
class Output_stream
{
public:
	virtual void write(T value) = 0;
};

template <typename T>
class String_output_stream : public Output_stream<T>
{
public:
	std::basic_ostringstream<T> string_stream;

	virtual void write(T value) override
	{
		string_stream.put(value);
	}
};

template <typename T>
class Basic_input_stream : public Input_stream<T>
{
public:
	std::basic_istream<T>* stream;

	Basic_input_stream(std::basic_istream<T>* stream)
		: stream{ stream }
	{
	}

	~Basic_input_stream()
	{
		delete stream;
	}

	virtual bool read(T& out_value) override
	{
		stream->get(out_value);
		return !stream->fail();
	}
};

template <typename T>
class Queue_stream : public Input_stream<T>, public Output_stream<T>
{
public:
	virtual bool read(T& out_value) override
	{
		if (!queue.empty())
		{
			out_value = queue.front();
			queue.pop();
			return true;
		}
		return false;
	}

	virtual void write(T value) override
	{
		queue.push(value);
	}

private:
	std::queue<T> queue;
};