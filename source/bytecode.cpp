
#include "bytecode.h"

byte* bytecode::get_start_pointer()
{
	return &bytes[0];
}

byte* bytecode::get_end_pointer()
{
	return &bytes[bytes.size()];
}

void bytecode::align(int size)
{
	auto mod = bytes.size() % size;
	if (mod)
	{
		auto new_size = bytes.size() + (size - mod);
		bytes.resize(new_size);
	}
}