#include "call_frame.h"

call_frame::call_frame(rt::function& function, cell* start)
	: function { function }
	, start { start }
{
	ip = function.bytecode.get_start_pointer();
}