#pragma once
#include "grid.h"

namespace std
{
    template <>
    struct hash<GridSlot>
    {
        size_t operator()(const GridSlot &grid_slot) const
        {
            return std::hash<int>()(grid_slot.column) ^ std::hash<int>()(grid_slot.row) ^ std::hash<bool>()(grid_slot.is_empty);
        }
    };
}