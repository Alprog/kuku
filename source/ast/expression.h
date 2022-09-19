
#pragma once

class compiler;

namespace ast
{
	class expression
	{
	public:
		virtual void compile(compiler& compiler) = 0;
	};
}