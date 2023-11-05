#include "cell.h"

cell::cell(int integer)
	: integer { integer }
{
}

bool cell::operator==(const cell& other) const
{
	return integer == other.integer;
}

bool cell::operator!=(const cell& other) const
{
	return integer != other.integer;
}