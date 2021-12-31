
#include "range.h"

Range::Range(Position start, Position end)
    : start{ start }
    , end{ end }
{
}

bool Range::contains(Position position)
{
    return position >= start && position < end;
}