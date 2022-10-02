
#pragma once

class compiler;

namespace ast
{
	class expression
	{
	public:
		virtual ~expression() = default;

		virtual void compile(compiler& compiler) = 0;
	};
}