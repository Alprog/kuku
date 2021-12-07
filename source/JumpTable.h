
#pragma once

class Routine;

using ExecuteFunctionPtr = void(*)(Routine&);

struct JumpTable
{
	static ExecuteFunctionPtr ExecuteFunction[256];

	static void Init();
};
