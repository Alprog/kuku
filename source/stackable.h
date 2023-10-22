#pragma once

#include <vector>

template <typename base>
struct stackable : public base
{
public:
	using base::base;

	void push_state()
	{
		state_stack.push(*this);
	}

	void pop_state()
	{
		static_cast<base&>(*this) = state_stack.top();
		state_stack.pop();
	}

	std::stack<base> state_stack;
};