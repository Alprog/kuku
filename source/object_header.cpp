
#include "object_header.h"

object_header::object_header(::class_index class_index)
	: class_index { class_index }
	, guid { 0 }
{
	data = nullptr;
}

void object_header::destroy()
{
	class_index = 0;
	if (data != nullptr)
	{
		delete data;
	}
}