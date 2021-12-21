
#pragma once

class Routine;

constexpr size_t INSTRUCTION_COUNT = 256;

using ExecuteFunctionPtr = void(*)(Routine&);
using GetSizeFunctionPtr = size_t(*)();

struct JumpTable
{
	static ExecuteFunctionPtr ExecuteFunction[INSTRUCTION_COUNT];
	static GetSizeFunctionPtr GetSizeFunction[INSTRUCTION_COUNT];

	static void Init();
};
