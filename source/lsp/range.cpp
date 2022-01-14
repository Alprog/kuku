
#include "range.h"

namespace lsp
{
    range::range(position start, position end)
        : start{ start }
        , end{ end }
    {
    }

    bool range::contains(position position)
    {
        return position >= start && position < end;
    }
}