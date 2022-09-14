
#pragma once

class compiler;

namespace ast
{
	class operand
	{
		virtual void compile(compiler& compile) {};
	};
}